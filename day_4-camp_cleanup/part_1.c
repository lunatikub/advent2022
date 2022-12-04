#include <stdio.h>

typedef struct section {
  unsigned from;
  unsigned to;
} section_t;

typedef struct pair {
  section_t s1;
  section_t s2;
} pair_t;

//#include "sample.h"
#include "puzzle.h"

int main(void) {
  unsigned overlap = 0;

  for (unsigned i = 0; i < NR_PAIR; ++i) {
    const section_t *s1 = &assignments[i].s1;
    const section_t *s2 = &assignments[i].s2;

    if (((s1->from <= s2->from) && (s1->to >= s2->to)) ||
        ((s2->from <= s1->from) && (s2->to >= s1->to))) {
      ++overlap;
    }
  }

  printf("overlap: %u\n", overlap);
  return 0;
}
