#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  char turn;
  unsigned blocks;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

#define N 0 // North
#define E 1 // East
#define S 2 // South
#define W 3 // Weast

#define SZ 500 // arbitrary value (assert if too small)
#define START_POS (SZ / 2)
static bool visited[SZ * SZ] = {false};

static int x = START_POS;
static int y = START_POS;
static int first_x = -1;
static int first_y = -1;

static unsigned next_dir(int dir, char turn) {
  if (turn == 'R') {
    if (dir == W) {
      return N;
    }
    return dir + 1;
  } else if (turn == 'L') {
    if (dir == N) {
      return W;
    }
    return dir - 1;
  }
  abort();
}

static void walk(int dir) {
  if (dir == N) {
    --y;
  } else if (dir == S) {
    ++y;
  } else if (dir == E) {
    ++x;
  } else if (dir == W) {
    --x;
  }
}

static void visit(void) {
  if (first_x == -1 && visited[y + x * SZ] == true) {
    first_x = x;
    first_y = y;
  }
  visited[y + x * SZ] = true;
}

static unsigned blocks(int x, int y) {
  return abs(x - START_POS) + abs(y - START_POS);
}

int main(void) {
  int dir = N;

  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    dir = next_dir(dir, in->turn);
    for (unsigned j = 0; j < in->blocks; ++j) {
      walk(dir);
      assert(x >= 0 && x < SZ);
      assert(y >= 0 && y < SZ);
      visit();
    }
  }
  assert(first_x != -1);

  printf("> part 1: %i\n", blocks(x, y));
  printf("> part 2: %u\n", blocks(first_x, first_y));
  return 0;
}
