#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  const char *c1; // compartment 1
  const char *c2; // compartment 2
  unsigned sz;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

#define ASCII_SZ 255

static void fill(const char *c1, bool *i1, const char *c2, bool *i2,
                 unsigned sz) {
  for (size_t i = 0; i < sz; ++i) {
    i1[(int)c1[i]] = true;
    i2[(int)c2[i]] = true;
  }
}

static char find_err(bool *i1, bool *i2) {
  for (size_t i = 0; i <= ASCII_SZ; ++i) {
    if (i1[i] == true && i2[i] == true) {
      return i;
    }
  }
  return 0;
}

static char find_badge(bool *i1, bool *i2, bool *i3) {
  for (unsigned i = 0; i < ASCII_SZ; ++i) {
    if (i1[i] == true && i2[i] == true && i3[i] == true) {
      return i;
    }
  }
  abort();
}

static int get_priority(char err) {
  if (err >= 'a' && err <= 'z') {
    return err - 'a' + 1;
  }
  return err - 'A' + 27;
}

static void reset(bool *i1, bool *i2, bool *i3) {
  memset(i1, 0, ASCII_SZ);
  memset(i2, 0, ASCII_SZ);
  memset(i3, 0, ASCII_SZ);
}

int main(void) {
  bool i1[ASCII_SZ];
  bool i2[ASCII_SZ];
  bool i3[ASCII_SZ];
  unsigned sum;

  sum = 0;
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    reset(i1, i2, i3);
    const input_t *in = &inputs[i];
    fill(in->c1, i1, in->c2, i2, in->sz);
    char err = find_err(i1, i2);
    int priority = get_priority(err);
    sum += priority;
  }
  printf("> part 1: %u\n", sum);

  sum = 0;
  for (unsigned i = 0; i < NR_INPUT / 3; ++i) {
    reset(i1, i2, i3);
    const input_t *in_1 = &inputs[i * 3];
    const input_t *in_2 = &inputs[i * 3 + 1];
    const input_t *in_3 = &inputs[i * 3 + 2];

    fill(in_1->c1, i1, in_1->c2, i1, in_1->sz);
    fill(in_2->c1, i2, in_2->c2, i2, in_2->sz);
    fill(in_3->c1, i3, in_3->c2, i3, in_3->sz);

    char badge = find_badge(i1, i2, i3);
    sum += get_priority(badge);
  }

  printf("> part 2: %u\n", sum);
  return 0;
}
