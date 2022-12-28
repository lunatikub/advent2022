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

static inline bool is_lower(char c) { return (c >= 'a' && c <= 'z'); }
static inline bool is_upper(char c) { return (c >= 'A' && c <= 'Z'); }

static  bool is_reacting(char c1, char c2) {
  if (is_lower(c1) == true &&
      is_upper(c2) == true &&
      (c1 - 'a' == c2 - 'A')) {
    return true;
  }
  if (is_upper(c1) == true &&
      is_lower(c2) == true &&
      (c1 - 'A' == c2 - 'a')) {
    return true;
  }
  return false;
}

static void move(char *in, unsigned start, unsigned len, unsigned sz) {
  unsigned i;
  for (i = start; i < len - sz; ++i) {
    in[i] = in[i + sz];
  }
  in[i] = 0;
}

static unsigned fully_reaction(char *in) {
  unsigned i = 0;
  unsigned len = strlen(in);
  while (i < len - 1) {
    if (is_reacting(in[i], in[i + 1]) == true) {
      move(in, i, len, 2);
      i = 0;
      len -= 2;
    } else {
      ++i;
    }
  }
  len = strlen(in);
  return len;
}

static void remove_unit(char *in, unsigned c) {
  unsigned i = 0;
  unsigned len = strlen(in);
  while (i < len) {
    if (in[i] == (char)(c + 'a') || in[i] == (char)(c + 'A')) {
      move(in, i, len, 1);
      len--;;
    } else {
      ++i;
    }
  }
}

#define ALPHA_SZ 26

int main(void) {
  char *in = strdup(inputs[0].str);

  unsigned len = fully_reaction(in);
  printf("part 1: %u\n", len);

  unsigned min = strlen(in);
  for (unsigned letter = 0; letter < 26; ++letter) {
    strcpy(in, inputs[0].str);
    remove_unit(in, letter);
    len = fully_reaction(in);
    if (len < min) {
      min = len;
    }
  }
  printf("part 2: %u\n", min);

  free(in);
  return 0;
}
