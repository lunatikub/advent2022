#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#define FORWARD 1
#define DOWN 2
#define UP 3

typedef struct input {
  int cmd;
  int val;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

int main(void) {
  int horizontal = 0;
  int depth = 0;
  int depth_2 = 0;
  int aim = 0;

  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    if (in->cmd == FORWARD) {
      horizontal += in->val;
      depth_2 += aim * in->val;
    } else if (in->cmd == DOWN) {
      depth += in->val;
      aim += in->val;
    } else if (in->cmd == UP) {
      depth -= in->val;
      aim -= in->val;
    } else {
      abort();
    }
  }

  printf("> part 1: %u\n", horizontal * depth);
  printf("> part 2: %u\n", horizontal * depth_2);
  return 0;
}
