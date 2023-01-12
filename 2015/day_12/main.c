#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include <unistd.h>

typedef struct input {
  char *json;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

static bool is_digit(char c) {
  if (c >= '0' && c<= '9') {
    return true;
  }
  return false;
}

static int get_number(const char *json, unsigned *i) {
  int n = 0;
  int sign = json[*i - 1] == '-' ? -1 : 1;
  while (is_digit(json[*i])) {
    n *= 10;
    n += json[*i] - '0';
    ++(*i);
  }
  return n * sign;
}

static int json_count(const char *json) {
  int n = 0;
  for (unsigned i = 0; i < strlen(json); ++i) {
    if (is_digit(json[i])) {
      n += get_number(json, &i);
    }
  }
  return n;
}

int main(void) {
  int n = 0;
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    n += json_count(in->json);
  }
  printf("> part 1: %u\n", n);

  // Too long in C and pointless
  // Use a hack with a script python executed in the puzzle.sh
  printf("> part 2: %u\n", PART_2);
  return 0;
}
