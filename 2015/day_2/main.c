#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  unsigned l;
  unsigned h;
  unsigned w;
} input_t;

#ifdef PUZZLE
#include "puzzle.h"
#else
#include "sample.h"
#endif

int main(void) {
  unsigned part_1 = 0;
  unsigned part_2 = 0;

  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];

    // part 1
    unsigned lw = in->l * in->w;
    unsigned wh = in->w * in->h;
    unsigned hl = in->h * in->l;
    unsigned smallest = lw;
    if (wh < smallest) {
      smallest = wh;
    }
    if (hl < smallest) {
      smallest = hl;
    }
    part_1 += 2 * lw + 2 * wh + 2 * hl + smallest;

    // part 2
    unsigned ribbon = 0;
    if (in->l >= in->h && in->l >= in->w) {
      ribbon = 2 * in->h + 2 * in->w;
    } else if (in->h >= in->w && in->h >= in->l) {
      ribbon = 2 * in->w + 2 * in->l;
    } else if (in->w >= in->h && in->w >= in->l) {
      ribbon = 2 * in->h + 2 * in->l;
    } else {
      abort();
    }
    part_2 += in->h * in->l * in->w + ribbon;
  }

  printf("> part 1: %u\n", part_1);
  printf("> part 2: %u\n", part_2);
  return 0;
}
