#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#define ON true
#define OFF false

typedef struct input {
  const char *line;
} input_t;

#ifndef PUZZLE
#define NR_STEP 5
#include "sample.h"
#else
#define NR_STEP 100
#include "puzzle.h"
#endif

typedef struct grid {
  bool *lights;
  unsigned sz;
} grid_t;

static void set(grid_t *g, unsigned x, unsigned y, bool v) {
  g->lights[x + y * g->sz] = v;
}

static bool get(grid_t *g, unsigned x, unsigned y) {
  return g->lights[x + y * g->sz];
}

static void create(grid_t *g, unsigned sz) {
  g->lights = calloc(sizeof(bool), sz * sz);
  g->sz = sz;
}

static void destroy(grid_t *g) {
  free(g->lights);
}

static void init(grid_t *g) {
  for (unsigned y = 0; y < NR_INPUT; ++y) {
    const input_t *in = &inputs[y];
    for (unsigned x = 0; x < strlen(in->line); ++x) {
      if (in->line[x] == '#') {
        set(g, x, y, ON);
      } else if (in->line[x] == '.') {
        set(g, x, y, OFF);
      } else {
        abort();
      }
    }
  }

}

/**
 * 123
 * 8#4
 * 765
 */
static unsigned neighbors(grid_t *g, int x, int y) {
  unsigned n = 0;

  for (int dy = -1; dy <= 1; ++dy) {
    for (int dx = -1; dx <= 1; ++dx) {
      if ((dx == 0 && dy == 0) || ((dx + x) < 0) ||
          ((dx + x) > (int)g->sz - 1) || ((dy + y) < 0) ||
          ((dy + y) > (int)g->sz - 1)) {
        continue;
      }
      n += get(g, x + dx, y + dy) == ON ? 1 : 0;
    }
  }
  return n;
}

/**
 * A light which is on stays on when 2 or 3 neighbors are on, and turns off otherwise.
 * A light which is off turns on if exactly 3 neighbors are on, and stays off otherwise.
 */
static void step(grid_t *src, grid_t *dst) {
  for (unsigned y = 0; y < src->sz; ++y) {
    for (unsigned x = 0; x < src->sz; ++x) {
      unsigned n = neighbors(src, x, y);
      if (get(src, x, y) == ON) {
        if (n == 2 || n == 3) {
          set(dst, x, y, ON);
        } else {
          set(dst, x, y, OFF);
        }
      } else {
        if (n == 3) {
          set(dst, x, y, ON);
        } else {
          set(dst, x, y, OFF);
        }
      }
    }
  }
}

static unsigned count(grid_t *g) {
  unsigned n = 0;
  for (unsigned y = 0; y < g->sz; ++y) {
    for (unsigned x = 0; x < g->sz; ++x) {
      n += get(g, x, y) == ON;
    }
  }
  return n;
}

static void corners(grid_t *g) {
  unsigned r = g->sz - 1; // right limit
  set(g, 0, 0, ON);
  set(g, 0, r, ON);
  set(g, r, 0, ON);
  set(g, r, r, ON);
}

static void swap(grid_t **g1, grid_t **g2) {
  grid_t *tmp = *g1;
  *g1 = *g2;
  *g2 = tmp;
}

int main(void) {
  grid_t g1;
  grid_t g2;
  grid_t *src = &g1;
  grid_t *dst = &g2;

  create(src, NR_INPUT);
  create(dst, NR_INPUT);

  init(src);
  for (unsigned s = 0; s < NR_STEP; ++s) {
    step(src, dst);
    swap(&src, &dst);
  }
  printf("> part 1: %u\n", count(src));

  init(src);
  for (unsigned s = 0; s < NR_STEP; ++s) {
    corners(src);
    step(src, dst);
    swap(&src, &dst);
  }
  corners(src);
  printf("> part 2: %u\n", count(src));

  destroy(&g1);
  destroy(&g2);
  return 0;
}
