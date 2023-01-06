#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  unsigned s1_from;
  unsigned s1_to;
  unsigned s2_from;
  unsigned s2_to;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

int main(void) {
  unsigned overlap_p1 = 0;
  unsigned overlap_p2 = 0;

  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    if (((in->s1_from <= in->s2_from) && (in->s1_to >= in->s2_to)) ||
        ((in->s2_from <= in->s1_from) && (in->s2_to >= in->s1_to))) {
      ++overlap_p1;
    }
    if (!((in->s2_to < in->s1_from) || (in->s2_from > in->s1_to))) {
      ++overlap_p2;
    }
  }
  printf("> part 1: %u\n", overlap_p1);
  printf("> part 2: %u\n", overlap_p2);
  return 0;
}
