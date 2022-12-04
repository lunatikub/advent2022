#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

struct ruckstack {
  char *c1;  // compartment 1
  char *c2;  // compartment 2
  size_t sz; // size of the compartment
};

//#include "sample.h"
#include "puzzle.h"

#define ASCII_SZ 255

static void fill_items(const struct ruckstack *r, bool *items) {
  memset(items, 0, sizeof(bool) * ASCII_SZ);
  for (size_t i = 0; i < r->sz; ++i) {
    items[(int)r->c1[i]] = true;
    items[(int)r->c2[i]] = true;
  }
}

static char find_badge(bool *i1, bool *i2, bool *i3) {
  for (unsigned i = 0; i < ASCII_SZ; ++i) {
    if (i1[i] == true && i2[i] == true && i3[i] == true) {
      return i;
    }
  }
  return 0;
}

static int get_priority(char err) {
  if (err >= 'a' && err <= 'z') {
    return err - 'a' + 1;
  }
  return err - 'A' + 27;
}

int main(void) {
  bool i1[255] = { }; // items of the group 1
  bool i2[255] = { }; // items of the group 2
  bool i3[255] = { }; // items of the group 3

  unsigned sum = 0;

  for (int i = 0; i < NR_RUCKSTACK / 3; i++) {
    const struct ruckstack *r1 = &ruckstacks[i * 3];
    const struct ruckstack *r2 = &ruckstacks[i * 3 + 1];
    const struct ruckstack *r3 = &ruckstacks[i * 3 + 2];

    fill_items(r1, i1);
    fill_items(r2, i2);
    fill_items(r3, i3);

    char badge = find_badge(i1, i2, i3);
    sum += get_priority(badge);
  }

  printf("sum: %u\n", sum);
  return 0;
}
