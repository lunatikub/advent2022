#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//#include "sample.h"
#include "puzzle.h"

#define ALPHA_SZ 26
#define MARKER_SZ 14

static bool is_marker(const char *stream) {
  bool alpha[ALPHA_SZ];
  memset(alpha, 0, sizeof(bool) * ALPHA_SZ);
  for (unsigned i = 0; i < MARKER_SZ; ++i) {
    if (alpha[(int)(stream[i] - 'a')] == true) {
      return false;
    }
    alpha[(int)(stream[i] - 'a')] = true;
  }
  return true;
}

int main(void) {
  for (unsigned i = 0; i < subroutine.nr; ++i) {
    if (is_marker(&subroutine.datastream[i]) == true) {
      printf("marker found: %.*s (%u)\n", MARKER_SZ, &subroutine.datastream[i],
             i + MARKER_SZ);
      break;
    }
  }
  return 0;
}
