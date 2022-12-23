#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  unsigned id; // identifer of the rectangle
  unsigned x;  // horizontal coordinate of the left top corner
  unsigned y;  // vertical coordinate of the left top corner
  unsigned w;  // width of the rectangle
  unsigned h;  // height of the rectangle
} input_t;

//#include "sample.h"
#include "puzzle.h"

#define SZ 1000
static unsigned grid[SZ][SZ];

static void fill_grid_with_puzzle(void) {
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    for (unsigned x = in->x; x < in->x + in->w; ++x) {
      assert(x < SZ);
      for (unsigned y = in->y; y < in->y + in->h; ++y) {
        assert(y < SZ);
        grid[x][y]++;
      }
    }
  }
}

static unsigned count_square(unsigned threshold) {
  unsigned n = 0;
  for (unsigned x = 0; x < SZ; ++x) {
    for (unsigned y = 0; y < SZ; ++y) {
      if (grid[x][y] >= threshold) {
        n++;
      }
    }
  }
  return n;
}

static const input_t *find_rect(unsigned x, unsigned y) {
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    if (in->x == x && in->y == y) {
      return in;
    }
  }
  return NULL;
}

static bool rect_is_overlapped(const input_t *in) {
  for (unsigned x = 0; x < in->w; ++x) {
    for (unsigned y = 0; y < in->h; ++y) {
      if (grid[in->x + x][in->y + y] != 1) {
        return true;
      }
    }
  }
  return false;
}

static const input_t *find_rect_not_overlapped(void) {
  unsigned x;
  unsigned y;
  for (x = 0; x < SZ; ++x) {
    for (y = 0; y < SZ; ++y) {
      if (grid[x][y] == 1) {
        const input_t *in = find_rect(x, y);
        if (in != NULL && rect_is_overlapped(in) == false) {
          return in;
        }
      }
    }
  }
  return NULL;
}

int main(void) {
  fill_grid_with_puzzle();

  // part 1
  unsigned squares = count_square(2);
  printf("> part_1: %u squares\n", squares);

  // part 2
  const input_t *in = find_rect_not_overlapped();
  assert(in != NULL);
  printf("> part_2: id: %u (x:%u, y:%u, w:%u, h:%u)\n", in->id, in->x, in->y,
         in->w, in->h);
  return 0;
}
