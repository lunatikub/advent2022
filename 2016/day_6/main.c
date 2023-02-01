#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  const char *str;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

#define ALPHA_SZ 26

int main(void) {
  unsigned len = strlen(inputs[0].str);
  char *message_part_1 = malloc(len + 1);
  char *message_part_2 = malloc(len + 1);

  for (unsigned i = 0; i < len; ++i) {
    unsigned count[ALPHA_SZ] = { };
    for (unsigned j = 0; j < NR_INPUT; ++j) {
      const char *in = inputs[j].str;
      count[in[i] - 'a']++;
    }
    unsigned most = 0;
    unsigned less = 0;
    for (unsigned j = 1; j < ALPHA_SZ; ++j) {
      if (count[j] > count[most]) {
        most = j;
      }
      if (count[j] != 0 && count[j] < count[less]) {
        less = j;
      }
    }
    message_part_1[i] = most + 'a';
    message_part_2[i] = less + 'a';
  }

  printf("> part 1: %s\n", message_part_1);
  printf("> part 2: %s\n", message_part_2);

  free(message_part_1);
  free(message_part_2);
  return 0;
}
