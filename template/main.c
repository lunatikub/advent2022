#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

int main(void) {
   for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    (void)in;
  }
 printf("> part 1: %u\n", 0);
  printf("> part 2: %u\n", 0);
  return 0;
}
