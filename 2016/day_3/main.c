#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  unsigned s1; // side 1
  unsigned s2; // side 2
  unsigned s3; // side 3
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

static bool is_valid_triangle(unsigned s1, unsigned s2, unsigned s3) {
  if ((s1 + s2 <= s3) || (s2 + s3 <= s1) || (s3 + s1 <= s2)) {
    return false;
  }
  return true;
}

int main(void) {
  unsigned nr_valid;

  nr_valid = 0;
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    if (is_valid_triangle(in->s1, in->s2, in->s3) == true) {
      ++nr_valid;
    }
  }
  printf("> part 1: %u\n", nr_valid);

  nr_valid = 0;
  for (unsigned i = 0; i < NR_INPUT; i += 3) {
    const input_t *in_1 = &inputs[i + 0];
    const input_t *in_2 = &inputs[i + 1];
    const input_t *in_3 = &inputs[i + 2];
    if (is_valid_triangle(in_1->s1, in_2->s1, in_3->s1) == true) {
      ++nr_valid;
    }
    if (is_valid_triangle(in_1->s2, in_2->s2, in_3->s2) == true) {
      ++nr_valid;
    }
    if (is_valid_triangle(in_1->s3, in_2->s3, in_3->s3) == true) {
      ++nr_valid;
    }
  }
  printf("> part 2: %u\n", nr_valid);
  return 0;
}

