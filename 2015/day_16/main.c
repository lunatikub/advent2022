#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#define UNDEFINED -1

enum compound {
  CHILDREN = 0,
  CATS,
  SAMOYEDS,
  POMERANIANS,
  AKITAS,
  VIZSLAS,
  GOLDFISH,
  TREES,
  CARS,
  PERFUMES,
  NR_COMPUND,
};

static const int compunds[NR_COMPUND] = {
    3, 7, 2, 3, 0, 0, 5, 3, 2, 1,
};

typedef struct input {
  int compunds[NR_COMPUND];
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

static bool is_sue_part_1(const input_t *in) {
  for (unsigned i = 0; i < NR_COMPUND; ++i) {
    if (in->compunds[i] != UNDEFINED && in->compunds[i] != compunds[i]) {
      return false;
    }
  }
  return true;
}

static bool is_sue_part_2(const input_t *in) {
  for (unsigned i = 0; i < NR_COMPUND; ++i) {
    if (in->compunds[i] != UNDEFINED) {
      switch (i) {
      case CATS:
      case TREES:
        if (in->compunds[i] <= compunds[i]) {
          return false;
        }
        break;
      case POMERANIANS:
      case GOLDFISH:
        if (in->compunds[i] >= compunds[i]) {
          return false;
        }
        break;
      default:
        if (in->compunds[i] != compunds[i]) {
          return false;
        }
        break;
      };
    }
  }
  return true;
}

int main(void) {
  unsigned i;

  for (i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    if (is_sue_part_1(in) == true) {
      break;
    }
  }
  printf("> part 1: %i\n", i + 1);

  for (i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    if (is_sue_part_2(in) == true) {
      break;
    }
  }
  printf("> part 2: %u\n", i + 1);

  return 0;
}
