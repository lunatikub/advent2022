#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#define P 1  // plus '+'
#define M -1 // minus '-'

typedef struct input {
  int op;  // operator
  int val; // value
} input_t;

#ifdef PUZZLE
#include "puzzle.h"
#else
#include "sample.h"
#endif

#define SZ 200000
static bool freqs[SZ * 2] = {false};

static bool solve_puzzle(int *freq) {
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *p = &inputs[i];
    *freq += (p->op * p->val);
    assert(*freq + SZ > 0 && *freq < SZ * 2);
    if (freqs[*freq + SZ] == true) {
      return true;
    }
    freqs[*freq + SZ] = true;
  }
  return false;
}

int main(void) {
  bool found = false;
  int freq = 0;

  found = solve_puzzle(&freq);
  printf("> part 1: %u\n", freq);

  while (found == false) {
    found = solve_puzzle(&freq);
  }
  printf("> part 2: %u\n", freq);

  return 0;
}
