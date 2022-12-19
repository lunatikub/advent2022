#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned l;
  unsigned h;
  unsigned w;
} dim_t;

#include "puzzle.h"

int main(void) {

  unsigned ribbon_feet = 0;

  for (unsigned i = 0; i < NR_DIM; ++i) {
    const dim_t *d = &dims[i];

    unsigned ribbon = 0;

    if (d->l >= d->h && d->l >= d->w) {
      ribbon = 2 * d->h + 2 * d->w;
    } else if (d->h >= d->w && d->h >= d->l) {
      ribbon = 2 * d->w + 2 * d->l;
    } else if (d->w >= d->h && d->w >= d->l) {
      ribbon = 2 * d->h + 2 * d->l;
    } else {
      abort();
    }

    ribbon += d->h * d->l * d->w;
    ribbon_feet += ribbon;
  }
  printf("> feet of ribbon: %u\n", ribbon_feet);

  return 0;
}
