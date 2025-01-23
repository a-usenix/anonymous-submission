/*
 * This file is distributed under the University of Illinois Open Source
 * License. See the LICENSE file for details.
 */
#include "llvm/Transforms/Instrumentation/ElkTemporalInst.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/IR/DiagnosticPrinter.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicsARM.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Instrumentation.h"
// #include "llvm/IR/TypeBuilder.h"
#include "llvm/Analysis/MemoryBuiltins.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/ValueTracking.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/IntrinsicsARM.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/MDBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/SpecialCaseList.h"
#include "llvm/Support/VirtualFileSystem.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Local.h" // For SplitBlockAndInsertIfThen

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <assert.h>
#include <stdio.h>

using namespace llvm;

static Value *CheckandTranslationPointer(IRBuilder<> &Builder, Value *Ptr) {
  Module *M = Builder.GetInsertBlock()->getParent()->getParent();
  LLVMContext &Context = M->getContext();

  Type *PtrType = Type::getInt8PtrTy(Context);

  FunctionType *RecoverAddressFuncType =
      FunctionType::get(PtrType, {PtrType}, false);

  FunctionCallee RecoverAddressFuncCallee =
      M->getOrInsertFunction("check_and_translation", RecoverAddressFuncType);
  Function *RecoverAddressFunc =
      dyn_cast<Function>(RecoverAddressFuncCallee.getCallee());

  if (!RecoverAddressFunc) {
    return Ptr;
  }

  Value *CallPtr = Builder.CreateBitCast(Ptr, PtrType);
  Value *RecoveredPtr = Builder.CreateCall(RecoverAddressFunc, {CallPtr});

  if (!CastInst::isBitCastable(Type::getInt8PtrTy(Context), Ptr->getType())) {
    errs() << "Error: Cannot cast check_and_translation result to original type: "
           << *(Ptr->getType()) << "\n";
    return Ptr;
  }
  Value *ResultPtr = Builder.CreateBitCast(RecoveredPtr, Ptr->getType());
  return ResultPtr;
}


static Value *TranslationPointer(IRBuilder<> &Builder, Value *Ptr) {
  Module *M = Builder.GetInsertBlock()->getParent()->getParent();
  LLVMContext &Context = M->getContext();

  Type *PtrType = Type::getInt8PtrTy(Context);

  FunctionType *RecoverAddressFuncType =
      FunctionType::get(PtrType, {PtrType}, false);

  FunctionCallee RecoverAddressFuncCallee =
      M->getOrInsertFunction("translation_only", RecoverAddressFuncType);
  Function *RecoverAddressFunc =
      dyn_cast<Function>(RecoverAddressFuncCallee.getCallee());

  if (!RecoverAddressFunc) {
    return Ptr;
  }

  Value *CallPtr = Builder.CreateBitCast(Ptr, PtrType);
  Value *RecoveredPtr = Builder.CreateCall(RecoverAddressFunc, {CallPtr});

  if (!CastInst::isBitCastable(Type::getInt8PtrTy(Context), Ptr->getType())) {
    errs() << "Error: Cannot cast translation_only result to original type: "
           << *(Ptr->getType()) << "\n";
    return Ptr;
  }
  Value *ResultPtr = Builder.CreateBitCast(RecoveredPtr, Ptr->getType());
  return ResultPtr;
}


static Value *TranslationPointerforICmp(IRBuilder<> &Builder, Value *Ptr) {
  Module *M = Builder.GetInsertBlock()->getParent()->getParent();
  LLVMContext &Context = M->getContext();

  Type *PtrType = Type::getInt8PtrTy(Context);

  FunctionType *RecoverAddressFuncType =
      FunctionType::get(PtrType, {PtrType}, false);

  FunctionCallee RecoverAddressFuncCallee =
      M->getOrInsertFunction("icmp_translation", RecoverAddressFuncType);
  Function *RecoverAddressFunc =
      dyn_cast<Function>(RecoverAddressFuncCallee.getCallee());

  if (!RecoverAddressFunc) {
    return Ptr;
  }

  Value *CallPtr = Builder.CreateBitCast(Ptr, PtrType);
  Value *RecoveredPtr = Builder.CreateCall(RecoverAddressFunc, {CallPtr});

  if (!CastInst::isBitCastable(Type::getInt8PtrTy(Context), Ptr->getType())) {
    errs() << "Error: Cannot cast translation_only result to original type: "
           << *(Ptr->getType()) << "\n";
    return Ptr;
  }
  Value *ResultPtr = Builder.CreateBitCast(RecoveredPtr, Ptr->getType());
  return ResultPtr;
}

static StringRef analyzePointer(Instruction* I,
                                Value *Ptr, std::map<Value *,
                                std::set<Instruction *>> &mallocUsers,
                                std::map<Value *, int> &isPointerNotFree) {
  Value *Underlying = getUnderlyingObject(Ptr, 50);
  
  if (auto *callInst = dyn_cast<CallInst>(Underlying)) {
    Function *CalledFunc = callInst->getCalledFunction();
    if (CalledFunc && (CalledFunc->getName() == "malloc" ||
                       CalledFunc->getName() == "calloc" ||
                       CalledFunc->getName() == "realloc" ||
                       CalledFunc->getName() == "__wrap_malloc" ||
                       CalledFunc->getName() == "__wrap_calloc" ||
                       CalledFunc->getName() == "__wrap_realloc")
        && (isPointerNotFree[Underlying] == 1 || isPointerNotFree[Ptr] == 1)
    ) {
      return "FastPath";
    }
  }

  if (
    isa<AllocaInst>(Underlying) || isa<GlobalVariable>(Underlying) ||
    isa<AllocaInst>(Ptr) || isa<GlobalVariable>(Ptr)
  ) {
    return "Exclude";
  }

  Value *targetValue = nullptr;
  for (const auto &[key, value] : mallocUsers) {
    for (auto i : value) {
      if (i == I && (Ptr == key || Underlying == key)) targetValue = key;
    }
  }
  if (targetValue == nullptr) return "SlowPath";
  if (isPointerNotFree[targetValue] == 1) return "FastPath";

  return "SlowPath";
}

static void applyTranslation(Function &F, Instruction *I,
                             const TargetLibraryInfo &TLI, 
                             std::map<Value *, std::set<Instruction *>> &mallocUsers,
                             std::map<Value *, int> &isPointerNotFree) {
  IRBuilder<> Builder(I);
  if (auto *storeInst = dyn_cast<StoreInst>(I)) {
    Value *Ptr = storeInst->getPointerOperand();
    if (!Ptr->getType()->isPointerTy()) {
      return;
    }

    StringRef Path = analyzePointer(I, Ptr, mallocUsers, isPointerNotFree);
    Value *TransformedPtr = nullptr;

    if (Path == "FastPath") {
      TransformedPtr = TranslationPointer(Builder, Ptr);
    } else if (Path == "SlowPath") {
      TransformedPtr = CheckandTranslationPointer(Builder, Ptr);
    }

    if (TransformedPtr) {
      Value *CorrectedPtr =
          Builder.CreateBitCast(TransformedPtr, Ptr->getType());
      storeInst->setOperand(1, CorrectedPtr);
    }
  } 
  else if (auto *loadInst = dyn_cast<LoadInst>(I)) {
    Value *Ptr = loadInst->getPointerOperand();
    if (!Ptr->getType()->isPointerTy()) {
      return;
    }

    StringRef Path = analyzePointer(I, Ptr, mallocUsers, isPointerNotFree);
    if (Path == "Exclude") {
      return;
    }
    if (Path == "FastPath") {
      loadInst->setOperand(0, TranslationPointer(Builder, Ptr));
    } else if (Path == "SlowPath") {
      loadInst->setOperand(0, CheckandTranslationPointer(Builder, Ptr));
    }
  } 
  
  // else if (auto *PtrtoIntInst = dyn_cast<PtrToIntInst>(I)) {
  //   Value *Ptr = PtrtoIntInst->getPointerOperand();
  //   if (!Ptr->getType()->isPointerTy()) {
  //     return;
  //   }

  //   StringRef Path = analyzePointer(I, Ptr, mallocUsers);
  //   if (Path == "Exclude") {
  //     return;
  //   }
  //   if (Path == "FastPath") {
  //     auto *NewPTI = Builder.CreatePtrToInt(fastTransformPointer(Builder, Ptr), PtrtoIntInst->getType());
  //     PtrtoIntInst->replaceAllUsesWith(NewPTI);
  //     PtrtoIntInst->eraseFromParent();
  //   } else if (Path == "SlowPath") {
  //     auto *NewPTI = Builder.CreatePtrToInt(transformPointer(Builder, Ptr), PtrtoIntInst->getType());
  //     PtrtoIntInst->replaceAllUsesWith(NewPTI);
  //     PtrtoIntInst->eraseFromParent();
  //   }
  // }

  // else if (auto icmpInst = dyn_cast<ICmpInst>(I)) {
  //   Value *lhs = icmpInst->getOperand(0);
  //   Value *rhs = icmpInst->getOperand(1);
  //   bool isLhsPointer = lhs->getType()->isPointerTy();
  //   bool isRhsPointer = rhs->getType()->isPointerTy();
  //   if (isLhsPointer && isRhsPointer) {
  //     StringRef Path1 = analyzePointer(I, lhs, mallocUsers, isPointerNotFree);
  //     StringRef Path2 = analyzePointer(I, rhs, mallocUsers, isPointerNotFree);
  //     if (Path1 == "Exclude" || Path2 == "Exclude") return;
  //     icmpInst->setOperand(0, TranslationPointerforICmp(Builder, lhs));
  //     icmpInst->setOperand(1, TranslationPointerforICmp(Builder, rhs));
  //   }
  // }

  else if (auto *memSetInst = dyn_cast<MemSetInst>(I)) {
    Value *Dst = memSetInst->getRawDest();
    if (!Dst->getType()->isPointerTy()) {
      return;
    }

    StringRef Path = analyzePointer(I, Dst, mallocUsers, isPointerNotFree);
    if (Path == "Exclude") {
      return;
    }
    Value *TranslatedDst = (Path == "FastPath")
                               ? TranslationPointer(Builder, Dst)
                               : CheckandTranslationPointer(Builder, Dst);

    // New MemSet instruction
    Value *Length = memSetInst->getLength();
    Value *Value = memSetInst->getValue();
    Align Alignment = *memSetInst->getDestAlign();
    auto *NewMemSet =
        Builder.CreateMemSet(TranslatedDst, Value, Length, Alignment);
    memSetInst->replaceAllUsesWith(NewMemSet);
    memSetInst->eraseFromParent();
  }
  else if (auto *memTransferInst = dyn_cast<MemTransferInst>(I)) {
    Value *Src = memTransferInst->getRawSource();
    Value *Dst = memTransferInst->getRawDest();

    if (!Src->getType()->isPointerTy() || !Dst->getType()->isPointerTy()) {
      // errs() << "Error: MemTransferInst Src or Dst is not a pointer type!\n";
      return;
    }

    StringRef SrcPath = analyzePointer(I, Src, mallocUsers, isPointerNotFree);
    StringRef DstPath = analyzePointer(I, Dst, mallocUsers, isPointerNotFree);

    if (SrcPath == "Exclude" && DstPath == "Exclude") {
      errs() << "Skipping Translation for MemTransfer: Both Src and Dst are "
                "Exclude\n";
      return;
    }

    Value *TranslatedSrc = (SrcPath == "FastPath")
                               ? TranslationPointer(Builder, Src)
                               : CheckandTranslationPointer(Builder, Src);
    Value *TranslatedDst = (DstPath == "FastPath")
                               ? TranslationPointer(Builder, Dst)
                               : CheckandTranslationPointer(Builder, Dst);

    Value *Length = memTransferInst->getLength();
    Align SrcAlign = *memTransferInst->getSourceAlign();
    Align DstAlign = *memTransferInst->getDestAlign();
    bool IsVolatile = memTransferInst->isVolatile();

    auto *NewMemTransfer = Builder.CreateMemCpy(
        TranslatedDst, DstAlign, TranslatedSrc, SrcAlign, Length, IsVolatile);

    memTransferInst->replaceAllUsesWith(NewMemTransfer);
    memTransferInst->eraseFromParent();
  }

  else if (auto *callInst = dyn_cast<CallInst>(I)) {
    Function *calledFunction = callInst->getCalledFunction();
    if (calledFunction) {
      if (
        calledFunction->getName() == "malloc" || calledFunction->getName() == "__wrap_malloc" ||
        calledFunction->getName() == "calloc" || calledFunction->getName() == "__wrap_calloc" ||
        calledFunction->getName() == "realloc" || calledFunction->getName() == "__wrap_realloc"
      ) {
        Value *ptr = callInst;
        isPointerNotFree[ptr] = 1;
      }
      if (calledFunction->getName() == "free" || calledFunction->getName() == "__wrap_free") {
        Value *ptr = callInst->getArgOperand(0);
        isPointerNotFree[ptr] = 0;
      }
      if (calledFunction->getName() == "free" || calledFunction->getName() == "realloc")
        return;
      if (calledFunction->getName() == "check_and_translation" || calledFunction->getName() == "translation_only")
        return;
      LibFunc libFunc;
      if (!TLI.getLibFunc(*calledFunction, libFunc)) {
        return;
      }
      for (unsigned i = 0; i < callInst->arg_size(); ++i) {
        Value *Arg = callInst->getArgOperand(i);
        if (!Arg->getType()->isPointerTy()) {
          continue;
        }

        StringRef Path = analyzePointer(I, Arg, mallocUsers, isPointerNotFree);
        if (Path == "Exclude") {
          continue;
        }
        Value *TranslatedArg = (Path == "FastPath")
                                   ? TranslationPointer(Builder, Arg)
                                   : CheckandTranslationPointer(Builder, Arg);
        callInst->setArgOperand(i, TranslatedArg);
      }
    }
  } else if (auto *invokeInst = dyn_cast<InvokeInst>(I)) {
    Function *calledFunction = invokeInst->getCalledFunction();
    if (calledFunction) {
      if (
        calledFunction->getName() == "malloc" || calledFunction->getName() == "__wrap_malloc" ||
        calledFunction->getName() == "calloc" || calledFunction->getName() == "__wrap_calloc" ||
        calledFunction->getName() == "realloc" || calledFunction->getName() == "__wrap_realloc"
      ) {
        Value *ptr = invokeInst;
        isPointerNotFree[ptr] = 1;
      }
      if (calledFunction->getName() == "free" || calledFunction->getName() == "__wrap_free") {
        Value *ptr = invokeInst->getArgOperand(0);
        isPointerNotFree[ptr] = 0;
      }
      if (calledFunction->getName() == "free" || calledFunction->getName() == "realloc")
        return;
      if (calledFunction->getName() == "check_and_translation" || calledFunction->getName() == "translation_only")
        return;
      LibFunc libFunc;
      if (!TLI.getLibFunc(*calledFunction, libFunc)) {
        return;
      }
      for (unsigned i = 0; i < invokeInst->arg_size(); ++i) {
        Value *Arg = invokeInst->getArgOperand(i);

        if (!Arg->getType()->isPointerTy()) {
          continue;
        }

        StringRef Path = analyzePointer(I, Arg, mallocUsers, isPointerNotFree);
        if (Path == "Exclude") {
          continue;
        }

        Value *TranslatedArg = (Path == "FastPath")
                                   ? TranslationPointer(Builder, Arg)
                                   : CheckandTranslationPointer(Builder, Arg);
        invokeInst->setArgOperand(i, TranslatedArg);
      }
    }
  }
}

void findAllUsers(Value *V, std::set<Instruction *> &Result, std::set<Value *> &Visited) {
    if (Visited.find(V) != Visited.end()) return;
    Visited.insert(V);
    for (User *U : V->users()) {
        if (Instruction *Inst = dyn_cast<Instruction>(U)) {
            Result.insert(Inst);
            findAllUsers(Inst, Result, Visited);
        }
    }
}

#define DEBUG_TYPE "elk-temporal-inst"
PreservedAnalyses ElkTemporalInstPass::run(Module &M, ModuleAnalysisManager &AM) {
  errs() << "ELK-Temporal-Inst !!!" << "\n";
  errs() << M.getName() << "====================\n";

  auto &FAM =
      AM.getResult<llvm::FunctionAnalysisManagerModuleProxy>(M).getManager();
  const DataLayout *DL = &M.getDataLayout();
  /* for wasm */
  if (M.getName() == "hello.c") return PreservedAnalyses::none();
  /* for wasm */
  for (auto &F : M) {
      if (
        F.getName() == "check_and_translation" ||
        F.getName() == "translation_only" ||
        F.getName() == "hwrng_read" ||
        F.getName() == "periph_clk_en" || 
        F.getName() == "periph_clk_dis"
        || F.getName() == "check_and_translation_micro"
        // F.getName() == "mutex_unlock" ||
        // F.getName() == "mutex_lock_internal"
        ) {
      continue;
      }
    // excludes all the allocator utils
    if (
      F.getName() == "__wrap_malloc" || F.getName() == "__wrap_free" ||
      F.getName() == "__wrap_calloc" || F.getName() == "__wrap_realloc"
    ) {
      continue;
    }
    if (F.getName() == "setMPU" || F.getName() == "elk_init") continue;

    const TargetLibraryInfo &TLI =
        FAM.getResult<llvm::TargetLibraryAnalysis>(F);
    // if (F.isDeclaration())
    //   continue;

    std::vector<Instruction *> InstsToProcess;
    for (auto &BB : F) {
      for (auto &I : BB) {
        InstsToProcess.push_back(&I);
      }
    }

    //std::set<Instruction *> isPointerNotFree;
    std::map<Value *, std::set<Instruction *>> mallocUsers;
    std::set<Value *> Visited;
    std::map<Value *, int> isPointerNotFree;

    for (Instruction *I : InstsToProcess) {
      if (auto *callInst = dyn_cast<CallInst>(I)) {
        Function *calledFunction = callInst->getCalledFunction();
        if (calledFunction) {
          if (
            calledFunction->getName() == "malloc" || calledFunction->getName() == "__wrap_malloc" ||
            calledFunction->getName() == "calloc" || calledFunction->getName() == "__wrap_calloc" ||
            calledFunction->getName() == "realloc" || calledFunction->getName() == "__wrap_realloc"
          ) {
            Value* mallocPtr = callInst;
            findAllUsers(callInst, mallocUsers[mallocPtr], Visited);
          }
        }
      }
    }

    for (Instruction *I : InstsToProcess) {
      applyTranslation(F, I, TLI, mallocUsers, isPointerNotFree);
    }
  }

  return PreservedAnalyses::none();
}

namespace {
struct ElkTemporalInstLegacyPass : public ModulePass {

  static char ID;
  ElkTemporalInstLegacyPass() : ModulePass(ID) {
    initializeElkTemporalInstLegacyPassPass(
        *PassRegistry::getPassRegistry());
  }

  bool runOnModule(Module &M) override {
    errs() << "ElkTemporalInst" << "\n";
    return false;
  }
};
} // namespace

char ElkTemporalInstLegacyPass::ID = 0;
INITIALIZE_PASS_BEGIN(ElkTemporalInstLegacyPass, "elk-temporal-inst",
                      "ELK for temporal instrumentation", false,
                      false)
INITIALIZE_PASS_END(ElkTemporalInstLegacyPass, "elk-temporal-inst",
                    "ELK for temporal instrumentation", false,
                    false)

Pass *llvm::createElkTemporalInstLegacyPass() {
  return new ElkTemporalInstLegacyPass();
}
