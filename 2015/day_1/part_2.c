#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "puzzle.h"

int main(void) {

  int floor = 0;

  for (unsigned i = 0; i < strlen(puzzle); ++i) {
    if (puzzle[i] == '(') {
      ++floor;
    } else if (puzzle[i] == ')') {
      --floor;
    } else {
      abort();
    }

    if (floor == -1) {
      printf("> basement: %u\n", i + 1);
      break;
    }
  }

  return 0;
}
