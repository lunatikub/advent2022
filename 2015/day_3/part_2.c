#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static const char sample1[] = "^v";
static const char sample2[] = "^>v<";
static const char sample3[] = "^v^v^v^v^v";

#include "coord.h"
#include "puzzle.h"
#include "../../common/set.h"

static void resolve_puzzle(const char *in) {
  coord_t santa = { 0, 0 };
  coord_t robot = { 0, 0 };
  set_t houses;

  set_init(&houses, sizeof(coord_t));
  set_add(&houses, &santa);

  unsigned n = 0;
  for (unsigned i = 0; i < strlen(in); ++i) {
    coord_t *c = ((n++ % 2) == 0) ? &santa : &robot;
    coord_update(c, in[i]);
    set_add(&houses, c);
  }

  printf("> nr_house: %lu\n", houses.nr);
  set_free(&houses);
}

int main(void) {
  resolve_puzzle(sample1);
  resolve_puzzle(sample2);
  resolve_puzzle(sample3);
  resolve_puzzle(puzzle);
  return 0;
}
