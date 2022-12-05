#include "move.h"
#include "crate.h"

#include "puzzle.h"
//#include "sample.h"

static void crate_pop_vec(crate_t *c, char *stack, unsigned n) {
  for (unsigned i = 0; i < n; ++i) {
    stack[n - i - 1] = crate_pop(c);
  }
}

static void crate_push_vec(crate_t *c, char *stack, unsigned n) {
  for (unsigned i = 0; i < n; ++i) {
    crate_push(c, stack[i]);
  }
}

int main(void) {
  char stack[STACK_SZ];

  for (unsigned m = 0; m < NR_MOVE; ++m) {
    const move_t *move = &moves[m];
    crate_t *from = &crates[move->from - 1];
    crate_t *to = &crates[move->to - 1];
    crate_pop_vec(from, stack, move->nr);
    crate_push_vec(to, stack, move->nr);
  }

  crate_result(crates, NR_CRATE);

  return 0;
}
