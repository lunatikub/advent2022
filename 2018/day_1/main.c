#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

#define P 1  // plus '+'
#define M -1 // minus '-'

typedef struct input {
  int op;  // operator
  int val; // value
} input_t;

//#include "sample.h"
#include "puzzle.h"

typedef struct freq {
  SLIST_ENTRY(freq) next;
  int val;
} freq_t;

SLIST_HEAD(, freq) freqs; // set of frequences reached

// return true if the element has been added
// return false if the element is already in the set
static bool add_freq(int f) {
  freq_t *iter;
  SLIST_FOREACH(iter, &freqs, next) {
    if (iter->val == f) {
      return false;
    }
  }
  iter = malloc(sizeof(*iter));
  iter->val = f;
  SLIST_INSERT_HEAD(&freqs, iter, next);
  return true;
}

static bool solve_puzzle(int *freq) {
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *p = &inputs[i];
    *freq += (p->op * p->val);
    if (add_freq(*freq) == false) {
      return true;
    }
  }
  return false;
}

int main(void) {
  bool found = false;
  int freq = 0;
  SLIST_INIT(&freqs);

  found = solve_puzzle(&freq);
  printf("> part_1: %u\n", freq);

  while (found == false) {
    found = solve_puzzle(&freq);
  }
  printf("> part 2: %u\n", freq);

  return 0;
}
