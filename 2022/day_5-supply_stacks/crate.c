#include <stdio.h>

#include "crate.h"

void crate_dump(const crate_t *c) {
  printf("[id:%u] %u {", c->id + 1, c->nr);
  for (unsigned i = 0; i < c->nr; ++i) {
    printf("%c,", c->stack[i]);
  }
  printf("}\n");
}

void crate_dump_all(const crate_t *c, unsigned nr) {
  for (unsigned i = 0; i < nr; ++i) {
    crate_dump(&c[i]);
  }
}

void crate_push(crate_t *c, char val) {
  c->stack[c->nr] = val;
  c->nr++;
}

char crate_pop(crate_t *c) {
  char val = c->stack[c->nr - 1];
  c->nr--;
  return val;
}

void crate_result(const crate_t *c, unsigned nr) {
  for (unsigned i = 0; i < nr; ++i) {
    printf("%c", c[i].stack[c[i].nr - 1]);
  }
  printf("\n");
}
