#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char sample1[] = ">";
static const char sample2[] = "^>v<";
static const char sample3[] = "^v^v^v^v^v";

#include "../../common/set.h"
#include "coord.h"
#include "puzzle.h"

static void resolve_puzzle(const char *in) {
  coord_t santa = {0, 0};
  set_t houses;

  set_init(&houses, sizeof(coord_t));
  set_add(&houses, &santa);

  for (unsigned i = 0; i < strlen(in); ++i) {
    coord_update(&santa, in[i]);
    set_add(&houses, &santa);
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
