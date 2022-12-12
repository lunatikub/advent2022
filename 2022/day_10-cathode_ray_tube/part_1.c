#include <stdio.h>
#include <stdint.h>

#include "inst.h"
#include "puzzle.h"

static uint32_t cycle = 1;
static uint32_t idx = 0;
static int X = 1;
static unsigned tot = 0;

static const uint32_t cycles[] = {
  20, 60, 100, 140, 180, 220,
};

static inline void cycle_step(void) {
  ++cycle;
  if (cycle == cycles[idx]) {
    tot += cycles[idx] * X;
    ++idx;
  }
}

int main(void) {

  for (unsigned i = 0; i < NR_INST; ++i) {
    const inst_t *inst = &insts[i];
    if (inst->type == INST_ADDX) {
      cycle_step();
    }
    X += inst->val;
    cycle_step();
  }
  printf("> %u\n", tot);

  return 0;
}
