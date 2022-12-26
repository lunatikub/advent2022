#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  char *str;
} input_t;

#ifdef PUZZLE
#include "puzzle.h"
#else
#include "sample.h"
#endif

int main(void) {
  int floor = 0;
  const char *str = inputs[0].str;
  bool part_2 = false;

  for (unsigned i = 0; i < strlen(str); ++i) {
    if (str[i] == '(') {
      ++floor;
    } else if (str[i] == ')') {
      --floor;
    } else {
      abort();
    }

    if (part_2 == false && floor == -1) {
      printf("> part 2: %u\n", i + 1);
      part_2 = true;
    }
  }

  printf("> part 1: %u\n", floor);
  return 0;
}
