#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#define TEASPOONS 100

typedef struct input {
  const char *ingredient;
  int capacity;
  int durability;
  int flavor;
  int texture;
  int calories;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

#define CALORIES_TARGET 500

int main(void) {
  unsigned part_1 = 0;
  unsigned part_2 = 0;
  unsigned score;
  int capacity;
  int durability;
  int flavor;
  int texture;
  int calories;

  for (unsigned i = 0; i < NR_COMBI; ++i) {
    const int *c = combis[i];

    capacity = 0;
    durability = 0;
    flavor = 0;
    texture = 0;
    calories = 0;

    for (unsigned j = 0; j < NR_INPUT; ++j) {
      const input_t *in = &inputs[j];
      capacity += c[j] * in->capacity;
      durability += c[j] * in->durability;
      flavor += c[j] * in->flavor;
      texture += c[j] * in->texture;
      calories += c[j] * in->calories;
    }

    if (capacity < 0)
      capacity = 0;
    if (durability < 0)
      durability = 0;
    if (flavor < 0)
      flavor = 0;
    if (texture < 0)
      texture = 0;

    score = capacity * durability * flavor * texture;
    if (score > part_1) {
      part_1 = score;
    }
    if (calories == CALORIES_TARGET && score > part_2) {
      part_2 = score;
    }
  }

  printf("> part 1: %u\n", part_1);
  printf("> part 2: %u\n", part_2);

  return 0;
}
