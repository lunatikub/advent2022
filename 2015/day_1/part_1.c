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
  }

  printf("> floor: %u\n", floor);
  return 0;
}
