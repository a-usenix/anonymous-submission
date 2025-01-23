#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xtimer.h"
//#include "malloc_thread_safe.h"

typedef uint8_t uint8;
typedef int8_t int8;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint32_t uint32;
typedef int32_t int32;
typedef float float32;
typedef double float64;
typedef uint64_t uint64;
typedef int64_t int64;

#define DWT_CYCCNT (*(uint32_t *) 0xE0001004)

int arrtest[30];


int main(void) {
  puts("\nHello malloc!\n");

  // printf("You are running RIOT on a(n) %s board.\n", RIOT_BOARD);
  // printf("This board features a(n) %s MCU.\n\n", RIOT_MCU);

  uint32_t start, end, clock;
  printf("tt test\n");
  
  unsigned tt_valid = __builtin_arm_cmse_TT((void *) 0x080173f4) >> 16;
  printf("%d\n", (tt_valid & 0x01));

  char *data8 = (char *)malloc(sizeof(char) * 1);
  *(data8 + 19) = 'b';
  printf("store success\n");
  printf("data8 address: %p\n", data8 + 19);
  printf("data8 value: %c\n\n", *(data8 + 19));
  
  start = xtimer_now_usec();
  enable_dwt();
  char *data = (char *)malloc(255);
  clock = DWT_CYCCNT;
  end = xtimer_now_usec();
  printf("malloc clock: %u\n", clock);
  printf("malloc time: %d ms\n", end - start);

  // malloc test
  *data = 'a';
  printf("%p\n", data);
  printf("%c\n", *data);

  start = xtimer_now_usec();
  enable_dwt();
  free(data);
  clock = DWT_CYCCNT;
  end = xtimer_now_usec();
  printf("free clock: %u\n", clock);
  printf("free time: %d ms\n", end - start);

  // use-after-free test
  // *data = 'a';
  // printf("%p\n", data);
  // printf("%c\n", *data);

  start = xtimer_now_usec();
  enable_dwt();
  char *data2 = (char *) calloc(255, sizeof(char));
  clock = DWT_CYCCNT;
  end = xtimer_now_usec();
  printf("calloc clock: %u\n", clock);
  printf("calloc time: %d ms\n", end - start);

  // calloc test
  *data2 = 'b';
  printf("%p\n", data2);
  printf("%c\n", *data2);

  start = xtimer_now_usec();
  enable_dwt();
  data2 = realloc(data2, sizeof(char));
  //realloc(data2, sizeof(char) * 255);
  clock = DWT_CYCCNT;
  end = xtimer_now_usec();
  printf("realloc clock: %u\n", clock);
  printf("realloc time: %d ms\n", end - start);

  // realloc test
  *(data2 + 33) = 'q';
  printf("%p\n", data2);
  printf("%c\n", *(data2 + 33));

  printf("DONE!!\n");
  return 0;
}
