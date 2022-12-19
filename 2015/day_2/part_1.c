#include <stdio.h>

typedef struct {
  unsigned l;
  unsigned h;
  unsigned w;
} dim_t;

#include "puzzle.h"

int main(void) {

  unsigned feet = 0;

  for (unsigned i = 0; i < NR_DIM; ++i) {
    const dim_t *d = &dims[i];

    unsigned lw = d->l * d->w;
    unsigned wh = d->w * d->h;
    unsigned hl = d->h * d->l;

    unsigned smallest = lw;
    if (wh < smallest) {
      smallest = wh;
    }
    if (hl < smallest) {
      smallest = hl;
    }

    unsigned square = 2 * lw + 2 * wh + 2 * hl + smallest;
    feet += square;
  }
  printf("> feet: %u\n", feet);

  return 0;
}
