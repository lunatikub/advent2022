#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define TURN_ON  1
#define TURN_OFF 2
#define TOGGLE   3

typedef struct coord {
  uint32_t x;
  uint32_t y;
} coord_t;

typedef struct inst {
  uint8_t type;
  coord_t from;
  coord_t to;
} inst_t;

#include "puzzle.h"

#define GRID_SZ 1000

static int32_t grid[GRID_SZ][GRID_SZ] = { 0 };

int main(void) {
  for (unsigned i = 0; i < NR_INST; ++i) {
    const inst_t *inst = &insts[i];
    assert(inst->from.x < GRID_SZ);
    assert(inst->from.y < GRID_SZ);
    assert(inst->to.x < GRID_SZ);
    assert(inst->to.y < GRID_SZ);
    for (uint32_t x = inst->from.x; x <= inst->to.x; ++x) {
      for (uint32_t y = inst->from.y; y <= inst->to.y; ++y) {
        if (inst->type == TURN_ON) {
          grid[x][y]++;
        } else if (inst->type == TURN_OFF) {
          if (grid[x][y] > 0) {
            grid[x][y]--;
          }
        } else if (inst->type == TOGGLE) {
          grid[x][y] += 2;
        } else {
          abort();
        }
      }
    }
  }

  uint32_t brightness = 0;
  for (uint32_t x = 0; x < GRID_SZ; ++x) {
    for (uint32_t y = 0; y < GRID_SZ; ++y) {
      brightness += grid[x][y];
    }
  }
  printf("> lights: %u\n", brightness);

  return 0;
}
