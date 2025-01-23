/*
 * Copyright (C) 2019 Gunar Schorcht
 *               2022 Otto-von-Guericke-Universität Magdeburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @{
 *
 * @file
 * @brief   Implements various POSIX syscalls
 * @author  Gunar Schorcht <gunar@schorcht.net>
 * @author  Marian Buschsieweke <marian.buschsieweke@ovgu.de>
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "architecture.h"
#include "assert.h"
#include "cpu.h"
#include "irq.h"
#include "kernel_defines.h"
#include "mutex.h"
#include "panic.h"
#include "log.h"

#include "periph/hwrng.h"

/*
 * mpu set header file
 */
#include "mpu_prog.h"
#include "mpu_defs.h"

/* micro evaluation */
#include "xtimer.h"
#define DWT_CYCCNT (*(uint32_t *) 0xE0001004)

extern void *__wrap_malloc(size_t size);
extern void __wrap_free(void *ptr);
extern void *__wrap_realloc(void *ptr, size_t size);

extern void *check_and_translation(const void *t_ptr);
extern void *translation_only(const void *t_ptr);

uint32_t SIZE_MAP[4] = { 0x4000, 0x100, 0x40, 0x10 };
//uint32_t SIZE_MAP[4] = { 0x4000, 0x1000, 0x1000, 0x1000 };
//uint32_t SIZE_MAP[4] = { 0x10, 0x100, 0x400, 0x4000 };
uint8_t SHIFT_MAP[4] = { 14, 8, 6, 4 };
//uint8_t SHIFT_MAP[4] = { 14, 12, 12, 12 };
//uint8_t SHIFT_MAP[4] = { 4, 8, 10, 14 };
unsigned int HEAPSIZE = 0x3C000; // region size. 0xF000 * 4 = 0x3C000. 
uint32_t REGION_SIZE = 0xF000;

static mutex_t _lock;
bool elk_malloc_inited = false; //checking allocator is initiated.

/*
 * elk data structure
 */
struct elk_freelist_s
{
  uintptr_t _reserved;
  struct elk_freelist_s *next;
};
typedef struct elk_freelist_s *elk_freelist_t;

struct elk_regioninfo_s
{
  elk_freelist_t freelist;
  void *freeptr;
  void *baseptr;
  void *endptr;
};
typedef struct elk_regioninfo_s *elk_regioninfo_t;

struct elk_regioninfo_s elk_REGION_INFO[4];

#ifdef ELK_PEAK_MEMORY_USAGE
/* for Memory Peak Usage Evaluation */
uintptr_t REGION_PEAK_ADDRESS[4] = { 0x20004000, 0x20013000, 0x20022000, 0x20031000 };
uint32_t validation_cnt = 0;
uint32_t translation_cnt = 0;

void print_memory_peak() {
  printf("validation Call Count: %u\n", validation_cnt);
  printf("translation Call Count: %u\n", translation_cnt);
  if (!elk_malloc_inited) return;
  printf("Memory Peak Usage: \n");
  uint32_t usage = 0;
  for (int i = 0; i < 4; i++) {
    printf("Region %d - 0x%p\n", (i + 1), REGION_PEAK_ADDRESS[i]);
    usage += REGION_PEAK_ADDRESS[i] - (uintptr_t) (elk_REGION_INFO + i)->baseptr;
  }
  printf("Use 0x%x Bytes.\n", usage);
}
#endif

/*
 * elk initialize mpu region, data structure
 */
bool elk_init(void) {
  elk_regioninfo_t info1 = elk_REGION_INFO;
  elk_regioninfo_t info2 = elk_REGION_INFO + 1;
  elk_regioninfo_t info3 = elk_REGION_INFO + 2;
  elk_regioninfo_t info4 = elk_REGION_INFO + 3;

  info1->freelist = NULL;
  info2->freelist = NULL;
  info3->freelist = NULL;
  info4->freelist = NULL;

  void* region1 = (void *)0x20004000; // 0xF000
  void* region2 = (void *)0x20013000; // 0xF000
  void* region3 = (void *)0x20022000; // 0xF000
  void* region4 = (void *)0x20031000; // 0xF000

  info1->freeptr = region1;
  info1->baseptr = region1;
  info1->endptr = region1 + 0xF000 - 1;

  info2->freeptr = region2;
  info2->baseptr = region2;
  info2->endptr = region2 + 0xF000 - 1;
  
  info3->freeptr = region3;
  info3->baseptr = region3;
  info3->endptr = region3 + 0xF000 - 1; 
  
  info4->freeptr = region4;
  info4->baseptr = region4;
  info4->endptr = region4 + 0xF000 - 1;

  setMPU(0UL, (void *)0x20004000, (void *)0x20012FFF, ARM_MPU_RW, 0UL, ARM_MPU_XN);
  setMPU(1UL, (void *)0x20013000, (void *)0x20021FFF, ARM_MPU_RW, 0UL, ARM_MPU_XN);
  setMPU(2UL, (void *)0x20022000, (void *)0x20030FFF, ARM_MPU_RW, 0UL, ARM_MPU_XN);
  setMPU(3UL, (void *)0x20031000, (void *)0x2003FFFF, ARM_MPU_RW, 0UL, ARM_MPU_XN);
  setMPU(7UL, (void *)0xC0040000, (void *)0xCFFFFFFF, ARM_MPU_RW, 0UL, ARM_MPU_XN);


  // Initialize HW Random Number Generator
  hwrng_init();

  elk_malloc_inited = true;
  //printf("HEAP INIT\n");

  return true;
}

#ifdef ELK_SECURITY
/* for Juliet */
uint32_t CWE415 = 0;
uint32_t CWE416 = 0;
uint32_t CWE590 = 0;
uint32_t CWE761 = 0;
/* for Juliet */
#endif
// Recover Pointer Address with TT Inst.
extern void *check_and_translation(const void *t_ptr) {
  #ifdef ELK_PEAK_MEMORY_USAGE
  validation_cnt++;
  #endif
  uint8_t tt_valid = __builtin_arm_cmse_TT(t_ptr) & 0x000000FF;
  if (!!(tt_valid ^ 0x07)) return t_ptr;
  uintptr_t r_ptr = (((uintptr_t) t_ptr & 0x000FFFFF) | 0x20000000);

  unsigned tt_val = __builtin_arm_cmse_TT((void *) r_ptr) & 0x000000FF;
  
  uint8_t *block_metadata = (uint8_t *) ((uintptr_t)(((uintptr_t)r_ptr >> SHIFT_MAP[tt_val]) << SHIFT_MAP[tt_val]) + (uintptr_t)((1 << SHIFT_MAP[tt_val]) - 1));
  
  uint8_t pointer_round = (uint8_t) (((uint32_t) t_ptr & 0x0FF00000) >> 20);
  #ifdef ELK_SECURITY
  /* for Juliet */
  if (*block_metadata != pointer_round) {
    CWE416++;
    printf("UAF Detected (check_and_translation). CWE-416 Count: %d\n", CWE416);
    return (void *) r_ptr;
  }
  /* for Juliet */
  #endif
  return !(*block_metadata ^ pointer_round) ? (void *) r_ptr : t_ptr;
}

// void *validation_condition(const void *t_ptr) {
//   if (!(0xC0040000 <= (uintptr_t) t_ptr && (uintptr_t) t_ptr <= 0xCFFFFFFF)) return t_ptr;
  
//   uintptr_t r_ptr = (((uintptr_t) t_ptr & 0x000FFFFF) | 0x20000000);

//   unsigned tt_val;
//   if (r_ptr <= 0x20012FFF) tt_val = 0;
//   else if (r_ptr <= 0x20021FFF) tt_val = 1;
//   else if (r_ptr <= 0x20030FFF) tt_val = 2;
//   else tt_val = 3;
//   uint8_t *block_metadata = (uint8_t *) ((uintptr_t)(((uintptr_t)r_ptr >> SHIFT_MAP[tt_val]) << SHIFT_MAP[tt_val]) + (uintptr_t)((1 << SHIFT_MAP[tt_val]) - 1));
//   uint8_t pointer_round = (uint8_t) (((uint32_t) t_ptr & 0x0FF00000) >> 20);
//   return !(*block_metadata ^ pointer_round) ? (void *) r_ptr : t_ptr;
// }

extern void *translation_only(const void *t_ptr) {
  #ifdef ELK_PEAK_MEMORY_USAGE
  translation_cnt++;
  #endif
  //uint8_t tt_valid = __builtin_arm_cmse_TT(t_ptr) & 0x000000FF;
  //if (!!(tt_valid ^ 0x07)) return t_ptr;
  //enable_dwt();
  uintptr_t r_ptr = (((uintptr_t) t_ptr & 0x000FFFFF) | 0x20000000);
  //uint32_t cycle = DWT_CYCCNT;
  //printf("%p translation_only cycle: %u\n", t_ptr, cycle);
  return (void *) r_ptr;
}

// extern void *icmp_translation(const void *t_ptr) {
//   //recoverAddress_cnt++;
//   uint8_t tt_valid = __builtin_arm_cmse_TT(t_ptr) & 0x000000FF;
//   if (!!(tt_valid ^ 0x07)) return t_ptr;
//   uintptr_t r_ptr = (((uintptr_t) t_ptr & 0x000FFFFF) | 0x20000000);
//   return (void *) r_ptr;
// }

/*
 * get real allocation size in elk
 */
uint8_t get_alloc_idx(size_t size) {
  // if (SIZE_MAP[0] > size) return 0;
  // else if (SIZE_MAP[1] > size) return 1;
  // else if (SIZE_MAP[2] > size) return 2;
  // else if (SIZE_MAP[3] > size) return 3;
  if (SIZE_MAP[3] > size) return 3;
  else if (SIZE_MAP[2] > size) return 2;
  else if (SIZE_MAP[1] > size) return 1;
  else if (SIZE_MAP[0] > size) return 0;
  else {
    LOG_ERROR("Too big size to allocate");
    hard_fault_default();
    //return 999;
  }
}

/*
 * elk allocator malloc
 */
// malloc()
extern void __attribute__((used)) *__wrap_malloc(size_t size) {
  assert(!irq_is_in());
  mutex_lock(&_lock);
  
  if (!elk_malloc_inited) elk_init();
  uint8_t idx = get_alloc_idx(size);
  size_t alloc_size = SIZE_MAP[idx];
  elk_regioninfo_t info = elk_REGION_INFO + idx;
  
  // Generate Random Number
  //enable_dwt();
  uint8_t random_value;
  hwrng_read(&random_value, sizeof(random_value));
  //uint32_t cycle = DWT_CYCCNT;
  //printf("RNG cycle: %u\n", cycle);
  random_value = 0x01;
  
  void *ptr;
  elk_freelist_t freelist = info->freelist;
  if (freelist != NULL) {
    info->freelist = freelist->next;
    ptr = (void *) freelist;
    uint8_t* block_metadata = (uint8_t *) (ptr + alloc_size - 1);
    *block_metadata = random_value;
    ptr = (void *) (((uintptr_t) ptr & (uintptr_t) 0x000FFFFF) | (uintptr_t) (0xC0000000 + 0x00100000 * random_value));
    #ifdef ELK_PEAK_MEMORY_USAGE
    /* for Memory Peak Usage Evaluation */
    REGION_PEAK_ADDRESS[idx] = (uintptr_t) block_metadata + 1 > REGION_PEAK_ADDRESS[idx] ? (uintptr_t) block_metadata + 1 : REGION_PEAK_ADDRESS[idx];
    /* for Memory Peak Usage Evaluation */
    #endif
    mutex_unlock(&_lock);
    return (void *) ptr;
  }

  ptr = info->freeptr;
  void *freeptr;
  freeptr = (void *) ptr + alloc_size;
  if(freeptr > info->endptr) {
    mutex_unlock(&_lock);
    LOG_ERROR("Region is full, can't alloc more");
    hard_fault_default();
  }
  uint8_t* block_metadata = (uint8_t *) (ptr + alloc_size - 1);
  *block_metadata = random_value;
  info->freeptr = freeptr;
  ptr = (void *) (((uintptr_t) ptr & (uintptr_t) 0x000FFFFF) | (uintptr_t) (0xC0000000 + 0x00100000 * random_value));
  #ifdef ELK_PEAK_MEMORY_USAGE
  /* for Memory Peak Usage Evaluation */
  REGION_PEAK_ADDRESS[idx] = (uintptr_t) block_metadata + 1 > REGION_PEAK_ADDRESS[idx] ? (uintptr_t) block_metadata + 1 : REGION_PEAK_ADDRESS[idx];
  /* for Memory Peak Usage Evaluation */
  #endif
  mutex_unlock(&_lock);
  return (void *) ptr;
}

// free()
extern void __attribute__((used)) __wrap_free(void *ptr) {
  assert(!irq_is_in());
  mutex_lock(&_lock);
  if (ptr == NULL) return;
  unsigned tt = __builtin_arm_cmse_TT(ptr);
  unsigned tt_valid = tt >> 16;
  /* for Juliet */
  if (!(tt_valid & 0x01)) {
    #ifdef ELK_SECURITY
    CWE590++;
    printf("Invalid Free! (Free of Memory not on the Heap) CWE-590 Count: %d\n", CWE590);
    mutex_unlock(&_lock);
    #else
    mutex_unlock(&_lock);
    LOG_ERROR("Invalid Free! (Free of Memory not on the Heap)");
    hard_fault_default();
    #endif
    return;
  }
  /* for Juliet */
  unsigned tt_isheap = tt & 0x000000FF;
  uintptr_t r_ptr = (((uintptr_t) ptr & 0x000FFFFF) | 0x20000000);
  unsigned idx = __builtin_arm_cmse_TT((void *)r_ptr) & 0x000000FF;
  elk_regioninfo_t info = &elk_REGION_INFO[idx];
  uintptr_t base = (((uintptr_t) r_ptr >> SHIFT_MAP[idx]) << SHIFT_MAP[idx]);
  /* for Juliet */
  if (r_ptr != base) {
    #ifdef ELK_SECURITY
    CWE761++;
    printf("Invalid Free! (Free of Pointer not at Start of Buffer) CWE-761 Count: %d\n", CWE761);
    mutex_unlock(&_lock);
    #else
    mutex_unlock(&_lock);
    LOG_ERROR("Invalid Free! (Free of Pointer not at Start of Buffer)");
    hard_fault_default();
    #endif
    return;
  }
  /* for Juliet */
  uintptr_t metadata_address = (base + (1 << SHIFT_MAP[idx]) - 1);
  uint8_t b_metadata = (uint8_t) *((uint8_t *) metadata_address);
  uint8_t pointer_round = (uint8_t) (((uint32_t) ptr & 0x0FF00000) >> 20);
  uint8_t* block_metadata = (uint8_t *) metadata_address;
  if (!(tt_isheap ^ 0x07)) {
    metadata_address = !(*block_metadata ^ pointer_round) ? metadata_address : (uintptr_t) ptr;
  }

  block_metadata = (uint8_t *) metadata_address;
  /* for Juliet */
  if (block_metadata == ptr) {
    #ifdef ELK_SECURITY
    CWE415++;
    printf("Double Free! CWE-415 Count: %d\n", CWE415);
    mutex_unlock(&_lock);
    #else
    mutex_unlock(&_lock);
    LOG_ERROR("Double Free!");
    hard_fault_default();
    #endif
    return;
  }
  /* for Juliet */
  *block_metadata = 0x00;
  elk_freelist_t newfreelist = (elk_freelist_t) base;
  elk_freelist_t oldfreelist = info->freelist;
  newfreelist->next = oldfreelist;
  info->freelist = newfreelist;
  mutex_unlock(&_lock);
  return;
}

void * __attribute__((used)) __wrap_calloc(size_t nmemb, size_t size) {
  /* some c libs don't perform proper overflow check (e.g. newlib < 4.0.0). Hence, we
    * just implement calloc on top of malloc ourselves. In addition to ensuring proper
    * overflow checks, this likely saves a bit of ROM */
  size_t total_size;
  if (__builtin_mul_overflow(nmemb, size, &total_size)) {
    return NULL;
  }
  void *res = __wrap_malloc(total_size);
  if (res) {
    memset(translation_only(res), 0, total_size);
  }
  return res;
}

extern void * __attribute__((used))__wrap_realloc(void *ptr, size_t size) {
  assert(!irq_is_in());
  if(ptr == NULL || size == 0) return malloc(size);
  void *newptr = __wrap_malloc(size);
  if(newptr == NULL) return NULL;
  memcpy(translation_only(newptr), translation_only(ptr), size);
  __wrap_free(ptr);
  return newptr;
}