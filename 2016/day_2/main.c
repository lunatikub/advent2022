#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  char *inst;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

#define SZ_1 3
static char grid_1[SZ_1 * SZ_1] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

#define SZ_2 5
static char grid_2[SZ_2 * SZ_2] = {'.', '.', '1', '.', '.', '.', '2', '3', '4',
                                   '.', '5', '6', '7', '8', '9', '.', 'A', 'B',
                                   'C', '.', '.', '.', 'D', '.', '.'};

static char get(char *g, unsigned x, unsigned y, unsigned sz) {
  return g[x + y * sz];
}

static void move(char m, char *g, unsigned sz, unsigned *x, unsigned *y) {
  unsigned dy = *y;
  unsigned dx = *x;

  switch (m) {
  case 'U':
    if (dy > 0 && get(g, dx, dy - 1, sz) != '.') {
      --dy;
    }
    break;
  case 'D':
    if (dy < sz - 1 && get(g, dx, dy + 1, sz) != '.') {
      ++dy;
    }
    break;
  case 'L':
    if (dx > 0 && get(g, dx - 1, dy, sz) != '.') {
      --dx;
    }
    break;
  case 'R':
    if (dx < sz - 1 && get(g, dx + 1, dy, sz) != '.') {
      ++dx;
    }
    break;
  default:
    abort();
  }

  *y = dy;
  *x = dx;
}

int main(void) {
  // grid_1 on '5'
  static unsigned x1 = 1;
  static unsigned y1 = 1;

  // grid_2 on '5'
  static unsigned x2 = 0;
  static unsigned y2 = 2;

  char *code_1 = malloc(sizeof(char) * NR_INPUT + 1);
  code_1[NR_INPUT] = '\0';
  char *code_2 = malloc(sizeof(char) * NR_INPUT + 1);
  code_2[NR_INPUT] = '\0';

  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    for (unsigned j = 0; j < strlen(in->inst); ++j) {
      move(in->inst[j], grid_1, SZ_1, &x1, &y1);
      move(in->inst[j], grid_2, SZ_2, &x2, &y2);
    }
    code_1[i] = get(grid_1, x1, y1, SZ_1);
    code_2[i] = get(grid_2, x2, y2, SZ_2);
  }

  printf("> part 1: %s\n", code_1);
  printf("> part 2: %s\n", code_2);

  free(code_1);
  free(code_2);
  return 0;
}
