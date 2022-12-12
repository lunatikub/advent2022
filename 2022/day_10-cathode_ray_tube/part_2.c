#include <stdio.h>

#include "inst.h"
#include "puzzle.h"

static int X = 1;
static int cycle = 1;
static int CRT = 0;

void cycle_step(void) {
  if (CRT == X - 1 || CRT == X + 1 || CRT == X) {
    printf("#");
  } else {
    printf(".");
  }
  if (cycle % 40 == 0) {
    printf("\n");
  }
  ++CRT;
  if (cycle % 40 == 0) {
    CRT = 0;
  }
  ++cycle;
}

int main(void) {

  for (unsigned i = 0; i < NR_INST; ++i) {
    const inst_t *inst = &insts[i];
    if (inst->type == INST_ADDX) {
      cycle_step();
    }
    cycle_step();
    X += inst->val;
  }

  return 0;
}
