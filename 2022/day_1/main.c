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

int main(void) {
  unsigned max[3] = { 0 };
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    unsigned current = 0;
    while (i < NR_INPUT && inputs[i].n != -1) {
      current += inputs[i++].n;
    }

    if (current > max[0]) {
      max[2] = max[1];
      max[1] = max[0];
      max[0] = current;
    } else if (current > max[1]) {
      max[2] = max[1];
      max[1] = current;
    } else if (current > max[2]) {
      max[2] = current;
    }
  }
  printf("> part 1: %u\n", max[0]);
  printf("> part 2: %u\n", max[0] + max[1] + max[2]);
  return 0;
}
