#include "move.h"
#include "crate.h"

#include "puzzle.h"
//#include "sample.h"

int main(void) {
  for (unsigned m = 0; m < NR_MOVE; ++m) {
    const move_t *move = &moves[m];
    for (unsigned n = 0; n < move->nr; ++n) {
      crate_t *from = &crates[move->from - 1];
      crate_t *to = &crates[move->to - 1];
      char val = crate_pop(from);
      crate_push(to, val);
    }
  }

  crate_result(crates, NR_CRATE);

  return 0;
}
