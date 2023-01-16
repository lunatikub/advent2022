#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  uint64_t n;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

uint64_t div_sum_part_1(uint64_t n) {
  uint64_t sum = 0;
  for (uint64_t i = 2; i < sqrt(n); ++i) {
    if (n % i == 0) {
      sum += i + n / i;
    }
  }
  return sum;
}

uint64_t div_sum_part_2(uint64_t n) {
  uint64_t sum = 0;
  for (uint64_t i = 2; i < sqrt(n); ++i) {
    if (n % i == 0) {
      if (i <= 50) {
        sum += n / i;
      }
      if (n / i <= 50) {
        sum += i;
      }
    }
  }
  return sum;
}

int main(void) {
  uint64_t target = inputs[0].n;
  uint64_t n = 2;
  uint64_t score = 0;

  while (score < target) {
    score = (div_sum_part_1(n) + n) * 10;
    ++n;
  }
  printf("> part 1: %lu\n", n - 1);

  score = 0;
  n = 2;
  while (score < target) {
    score = (div_sum_part_2(n) + n) * 11;
    ++n;
  }
  printf("> part 2: %lu\n", n - 1);

  return 0;
}
