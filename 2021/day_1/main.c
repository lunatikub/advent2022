#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  int n;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

static unsigned count_increased(const input_t *in) {
  unsigned n = 0;
  int prev = in[0].n;

  for (unsigned i = 1; i < NR_INPUT; ++i) {
    int curr = in[i].n;
    if (prev < curr)
      ++n;
    prev = curr;
  }
  return n;
}

int main(void) {
  printf("> part 1: %u\n", count_increased(inputs));

  input_t *in_dup = calloc(NR_INPUT, sizeof(input_t));
  for (unsigned i = 0; i < NR_INPUT - 2; ++i) {
    in_dup[i].n = inputs[i].n + inputs[i + 1].n + inputs[i + 2].n;
  }
  printf("> part 2: %u\n", count_increased(in_dup));
  free(in_dup);
  return 0;
}
