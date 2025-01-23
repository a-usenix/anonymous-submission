; ModuleID = 'zerofat_functions.c'
source_filename = "zerofat_functions.c"
target datalayout = "e-m:e-p:32:32-Fi8-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "thumbv8m.main-none-unknown-eabi"

@SIZE_TABLE = dso_local global [7 x i32] [i32 16, i32 256, i32 4096, i32 16384, i32 524287, i32 8191, i32 268435455], align 4
@ERROR_COUNT = dso_local global i32 0, align 4
@.str = private unnamed_addr constant [27 x i8] c"\0A ptr = %p, baseptr = %p\0A\0A\00", align 1

; Function Attrs: noinline nounwind optnone
define dso_local void @zerofat_error(i8* noundef %ptr, i8* noundef %baseptr) #0 {
entry:
  %ptr.addr = alloca i8*, align 4
  %baseptr.addr = alloca i8*, align 4
  store i8* %ptr, i8** %ptr.addr, align 4
  store i8* %baseptr, i8** %baseptr.addr, align 4
  %0 = load i8*, i8** %ptr.addr, align 4
  %1 = load i8*, i8** %baseptr.addr, align 4
  %call = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([27 x i8], [27 x i8]* @.str, i32 0, i32 0), i8* noundef %0, i8* noundef %1)
  %2 = load i32, i32* @ERROR_COUNT, align 4
  %inc = add i32 %2, 1
  store i32 %inc, i32* @ERROR_COUNT, align 4
  ret void
}

declare dso_local i32 @printf(i8* noundef, ...) #1

; Function Attrs: noinline nounwind optnone
define dso_local void @zerofat_oob_check(i8* noundef %ptr, i8* noundef %baseptr) #0 {
entry:
  %ptr.addr = alloca i8*, align 4
  %baseptr.addr = alloca i8*, align 4
  %tt_val = alloca i32, align 4
  %mask = alloca i32, align 4
  %size_idx = alloca i32, align 4
  %size = alloca i32, align 4
  %diff = alloca i32, align 4
  store i8* %ptr, i8** %ptr.addr, align 4
  store i8* %baseptr, i8** %baseptr.addr, align 4
  %0 = load i8*, i8** %baseptr.addr, align 4
  %1 = call i32 @llvm.arm.cmse.tt(i8* %0)
  store i32 %1, i32* %tt_val, align 4
  store i32 65536, i32* %mask, align 4
  %2 = load i32, i32* %tt_val, align 4
  %3 = load i32, i32* %mask, align 4
  %and = and i32 %2, %3
  %cmp = icmp eq i32 %and, 0
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  br label %return

if.end:                                           ; preds = %entry
  %4 = load i32, i32* %tt_val, align 4
  %and1 = and i32 %4, 255
  store i32 %and1, i32* %size_idx, align 4
  %5 = load i32, i32* %size_idx, align 4
  %arrayidx = getelementptr inbounds [7 x i32], [7 x i32]* @SIZE_TABLE, i32 0, i32 %5
  %6 = load i32, i32* %arrayidx, align 4
  store i32 %6, i32* %size, align 4
  %7 = load i8*, i8** %ptr.addr, align 4
  %8 = load i8*, i8** %baseptr.addr, align 4
  %sub.ptr.lhs.cast = ptrtoint i8* %7 to i32
  %sub.ptr.rhs.cast = ptrtoint i8* %8 to i32
  %sub.ptr.sub = sub i32 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast
  store i32 %sub.ptr.sub, i32* %diff, align 4
  %9 = load i32, i32* %diff, align 4
  %10 = load i32, i32* %size, align 4
  %cmp2 = icmp uge i32 %9, %10
  br i1 %cmp2, label %if.then3, label %if.end4

if.then3:                                         ; preds = %if.end
  %11 = load i8*, i8** %ptr.addr, align 4
  %12 = load i8*, i8** %baseptr.addr, align 4
  call void @zerofat_error(i8* noundef %11, i8* noundef %12)
  br label %if.end4

if.end4:                                          ; preds = %if.then3, %if.end
  br label %return

return:                                           ; preds = %if.end4, %if.then
  ret void
}

; Function Attrs: nounwind readnone
declare i32 @llvm.arm.cmse.tt(i8*) #2

; Function Attrs: noinline nounwind optnone
define dso_local i8* @zerofat_base(i8* noundef %_ptr) #0 {
entry:
  %_ptr.addr = alloca i8*, align 4
  %tt_val = alloca i32, align 4
  %size_idx = alloca i32, align 4
  %size = alloca i32, align 4
  %ptr_val = alloca i32, align 4
  %base = alloca i32, align 4
  store i8* %_ptr, i8** %_ptr.addr, align 4
  %0 = load i8*, i8** %_ptr.addr, align 4
  %1 = call i32 @llvm.arm.cmse.tt(i8* %0)
  store i32 %1, i32* %tt_val, align 4
  %2 = load i32, i32* %tt_val, align 4
  %and = and i32 %2, 255
  store i32 %and, i32* %size_idx, align 4
  %3 = load i32, i32* %size_idx, align 4
  %arrayidx = getelementptr inbounds [7 x i32], [7 x i32]* @SIZE_TABLE, i32 0, i32 %3
  %4 = load i32, i32* %arrayidx, align 4
  store i32 %4, i32* %size, align 4
  %5 = load i8*, i8** %_ptr.addr, align 4
  %6 = ptrtoint i8* %5 to i32
  store i32 %6, i32* %ptr_val, align 4
  %7 = load i32, i32* %ptr_val, align 4
  %8 = load i32, i32* %size, align 4
  %div = udiv i32 %7, %8
  %9 = load i32, i32* %size, align 4
  %mul = mul i32 %div, %9
  store i32 %mul, i32* %base, align 4
  %10 = load i32, i32* %base, align 4
  %11 = inttoptr i32 %10 to i8*
  ret i8* %11
}

attributes #0 = { noinline nounwind optnone "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="cortex-m33" "target-features"="+armv8-m.main,+dsp,+fp-armv8d16sp,+fp16,+hwdiv,+strict-align,+thumb-mode,+vfp2sp,+vfp3d16sp,+vfp4d16sp,-aes,-bf16,-cdecp0,-cdecp1,-cdecp2,-cdecp3,-cdecp4,-cdecp5,-cdecp6,-cdecp7,-crc,-crypto,-d32,-dotprod,-fp-armv8,-fp-armv8d16,-fp-armv8sp,-fp16fml,-fp64,-fullfp16,-hwdiv-arm,-i8mm,-lob,-mve,-mve.fp,-neon,-pacbti,-ras,-sb,-sha2,-vfp2,-vfp3,-vfp3d16,-vfp3sp,-vfp4,-vfp4d16,-vfp4sp" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="cortex-m33" "target-features"="+armv8-m.main,+dsp,+fp-armv8d16sp,+fp16,+hwdiv,+strict-align,+thumb-mode,+vfp2sp,+vfp3d16sp,+vfp4d16sp,-aes,-bf16,-cdecp0,-cdecp1,-cdecp2,-cdecp3,-cdecp4,-cdecp5,-cdecp6,-cdecp7,-crc,-crypto,-d32,-dotprod,-fp-armv8,-fp-armv8d16,-fp-armv8sp,-fp16fml,-fp64,-fullfp16,-hwdiv-arm,-i8mm,-lob,-mve,-mve.fp,-neon,-pacbti,-ras,-sb,-sha2,-vfp2,-vfp3,-vfp3d16,-vfp3sp,-vfp4,-vfp4d16,-vfp4sp" }
attributes #2 = { nounwind readnone }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 1, !"min_enum_size", i32 4}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{!"clang version 15.0.7 (https://github.com/pnu-csl/zerofat-llvm.git df1852624b71fee8a38f35f75082436335eac16a)"}
