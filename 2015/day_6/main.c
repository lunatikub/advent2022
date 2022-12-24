#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#define TURN_ON 1
#define TURN_OFF 2
#define TOGGLE 3

#define OFF 0
#define ON 1

typedef struct coord {
  unsigned x;
  unsigned y;
} coord_t;

typedef struct input {
  int type;
  coord_t from;
  coord_t to;
} input_t;

//#include "sample.
#include "puzzle.h"

#define GRID_SZ 1000
static int grid_1[GRID_SZ * GRID_SZ];
static int grid_2[GRID_SZ * GRID_SZ];

#define IDX(x, y) (x + y * GRID_SZ)

static unsigned grid_sum(int *g) {
  unsigned sum = 0;
  for (unsigned x = 0; x < GRID_SZ; ++x) {
    for (unsigned y = 0; y < GRID_SZ; ++y) {
      sum += g[IDX(x, y)];
    }
  }
  return sum;
}

static void input_check(const input_t *in) {
  assert(in->from.x < GRID_SZ);
  assert(in->from.y < GRID_SZ);
  assert(in->to.x < GRID_SZ);
  assert(in->to.y < GRID_SZ);
}

static void cell_set(const input_t *in, unsigned x, unsigned y) {
  if (in->type == TURN_ON) {
    grid_1[IDX(x, y)] = ON;
    grid_2[IDX(x, y)]++;
  } else if (in->type == TURN_OFF) {
    grid_1[IDX(x, y)] = OFF;
    if (grid_2[IDX(x, y)] > 0) {
      grid_2[IDX(x, y)]--;
    }
  } else if (in->type == TOGGLE) {
    grid_1[IDX(x, y)] = grid_1[IDX(x, y)] == ON ? OFF : ON;
    grid_2[IDX(x, y)] += 2;
  } else {
    abort();
  }
}

static void grid_fill(void) {
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    input_check(in);
    for (unsigned x = in->from.x; x <= in->to.x; ++x) {
      for (unsigned y = in->from.y; y <= in->to.y; ++y) {
        cell_set(in, x, y);
      }
    }
  }
}

int main(void) {
  grid_fill();
  printf("part 1: %u\n", grid_sum(grid_1));
  printf("part 2: %u\n", grid_sum(grid_2));
  return 0;
}
