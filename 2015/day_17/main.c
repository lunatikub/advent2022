#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  unsigned liter; // size of the container in liter
} input_t;

#ifdef PUZZLE
#include "puzzle.h"
#define TARGET 150
#else
#include "sample.h"
#define TARGET 25
#endif

static unsigned n;    // number of containers can contain TARGET
static unsigned *r_n; // number of containers can contain TARGET sorted by 'r'

/*
** nCr = (n r) = n! / r! x (r - n)!
*/
typedef struct combination {
  unsigned n;
  unsigned r;
  unsigned *idx;
  unsigned *combi;
} combination_t;

static void combination(combination_t *c) {
  unsigned liters = 0;
  for (unsigned i = 0; i < c->r; ++i) {
    liters += inputs[c->combi[i]].liter;
  }
  if (liters == TARGET) {
    r_n[c->r - 1]++;
    ++n;
  }
}

static void combination_init(combination_t *c, int n, int r) {
  c->n = n;
  c->r = r;
  c->idx = malloc(c->n * sizeof(unsigned));
  c->combi = malloc(c->r * sizeof(unsigned));
  for (unsigned i = 0; i < c->n; ++i) {
    c->idx[i] = i;
  }
}

static void combination_free(combination_t *c) {
  free(c->idx);
  free(c->combi);
}

static void combinations(combination_t *c, unsigned start, unsigned end,
                         unsigned idx) {
  if (idx == c->r) {
    combination(c);
    return;
  }
  for (unsigned i = start; i <= end && end - i + 1 > c->r - idx; ++i) {
    c->combi[idx] = c->idx[i];
    combinations(c, i + 1, end, idx + 1);
  }
}

int main() {
  combination_t c;
  r_n = calloc(NR_INPUT, sizeof(unsigned));

  for (unsigned r = 1; r <= NR_INPUT; ++r) {
    combination_init(&c, NR_INPUT, r);
    combinations(&c, 0, NR_INPUT, 0);
    combination_free(&c);
  }
  printf("part 1: %u\n", n);

  for (unsigned i = 0; i < NR_INPUT; ++i) {
    if (r_n[i] != 0) {
      printf("part 2: %u\n", r_n[i]);
      break;
    }
  }

  free(r_n);
  return 0;
}
