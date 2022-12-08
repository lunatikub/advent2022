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

static void fill_items(const struct ruckstack *r, bool *i1, bool *i2) {
  memset(i1, 0, sizeof(bool) * ASCII_SZ);
  memset(i2, 0, sizeof(bool) * ASCII_SZ);
  for (size_t i = 0; i < r->sz; ++i) {
    i1[(int)r->c1[i]] = true;
    i2[(int)r->c2[i]] = true;
  }
}

static char find_err_item(bool *i1, bool *i2) {
  for (size_t i = 0; i <= ASCII_SZ; ++i) {
    if (i1[i] == true && i2[i] == true) {
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
  bool i1[255] = { }; // items of the compartment 1
  bool i2[255] = { }; // items of the compartment 2

  unsigned sum = 0;

  for (int i = 0; i < NR_RUCKSTACK; ++i) {
    const struct ruckstack *r = &ruckstacks[i];
    fill_items(r, i1, i2);
    char err = find_err_item(i1, i2);
    int priority = get_priority(err);
    sum += priority;
  }

  printf("sum: %u\n", sum);
  return 0;
}
