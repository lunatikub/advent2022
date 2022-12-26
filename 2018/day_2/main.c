#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  char *str;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

#define ALPHA_SZ 26

int main(void) {
  unsigned count[ALPHA_SZ];
  unsigned twos = 0;
  unsigned threes = 0;

  // part 1
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    memset(count, 0, ALPHA_SZ * sizeof(unsigned));
    const char *str = inputs[i].str;
    for (unsigned j = 0; j < strlen(str); ++j) {
      count[str[j] - 'a']++;
    }
    bool has_two = false;
    bool has_three = false;
    for (unsigned j = 0; j < ALPHA_SZ; ++j) {
      if (count[j] == 2) {
        has_two = true;
      }
      if (count[j] == 3) {
        has_three = true;
      }
    }
    twos += has_two ? 1 : 0;
    threes += has_three ? 1 : 0;
  }
  printf("> part 1: %u\n", twos * threes);

  // part 2
  const char *src;
  const char *dst;
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    src = inputs[i].str;
    for (unsigned j = i + 1; j < NR_INPUT; j++) {
      dst = inputs[j].str;
      unsigned diff = 0;
      for (unsigned k = 0; k < strlen(src); ++k) {
        if (src[k] != dst[k]) {
          ++diff;
        }
      }
      if (diff == 1) {
        goto end;
      }
    }
  }

end:
  printf("> part 2: ");
  for (unsigned i = 0; i < strlen(src); ++i) {
    if (src[i] == dst[i]) {
      printf("%c", src[i]);
    }
  }
  printf("\n");

  return 0;
}
