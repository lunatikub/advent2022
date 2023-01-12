#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#define MAX_INIT_SZ 10

typedef struct input {
  unsigned init[MAX_INIT_SZ];
} input_t;

#ifdef PUZZLE
#include "puzzle.h"
#else
#include "sample.h"
#endif

#define SZ 4000000

static inline unsigned seq(unsigned *src, unsigned *dst, unsigned len) {
  unsigned dst_idx = 0;
  for (unsigned i = 0; i < len; ++i) {
    unsigned count = 0;
    unsigned n = src[i];
    while (src[i] == n && i < len) {
      ++count;
      ++i;
    }
    --i;
    dst[dst_idx++] = count;
    dst[dst_idx++] = n;
  }
  return dst_idx;
}

static inline void swap(unsigned **src, unsigned **dst) {
  unsigned *tmp = *src;
  *src = *dst;
  *dst = tmp;
}

#define PART_1 40
#define PART_2 50

int main(void) {
  unsigned *n1 = malloc(SZ * sizeof(unsigned));
  unsigned *n2 = malloc(SZ * sizeof(unsigned));

  unsigned *src = n1;
  unsigned *dst = n2;
  unsigned len = NR_INPUT;

  memcpy(src, inputs[0].init, len * sizeof(unsigned));

  for (unsigned i = 0; i < PART_1; ++i) {
    len = seq(src, dst, len);
    swap(&src, &dst);
  }
  printf("> part 1: %u\n", len);

  for (unsigned i = 0; i < PART_2 - PART_1; ++i) {
    len = seq(src, dst, len);
    swap(&src, &dst);
  }
  printf("> part 2: %u\n", len);

  free(n1);
  free(n2);
  return 0;
}
