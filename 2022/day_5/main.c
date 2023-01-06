#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#define STACK_SZ 255

typedef struct crate {
  char stack[STACK_SZ];
  unsigned nr;
  unsigned id;
} crate_t;

typedef struct input {
  unsigned nr;
  unsigned from;
  unsigned to;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

static void push(crate_t *c, char val) {
  c->stack[c->nr++] = val;
}

static char pop(crate_t *c) {
  return c->stack[--c->nr];
}

static void pop_vec(crate_t *c, char *stack, unsigned n) {
  for (unsigned i = 0; i < n; ++i) {
    stack[n - i - 1] = pop(c);
  }
}

static void push_vec(crate_t *c, char *stack, unsigned n) {
  for (unsigned i = 0; i < n; ++i) {
    push(c, stack[i]);
  }
}

void dump(const crate_t *c, unsigned part, unsigned nr) {
  printf("> part %u: ", part);
  for (unsigned i = 0; i < nr; ++i) {
    printf("%c", c[i].stack[c[i].nr - 1]);
  }
  printf("\n");
}

int main(void) {
  crate_t *crates_1 = malloc(sizeof(crates));
  memcpy(crates_1, crates, sizeof(crates));

  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    for (unsigned n = 0; n < in->nr; ++n) {
      push(&crates_1[in->to - 1], pop(&crates_1[in->from - 1]));
    }
  }
  dump(crates_1, 1, NR_CRATE);
  free(crates_1);

  crate_t *crates_2 = malloc(sizeof(crates));
  memcpy(crates_2, crates, sizeof(crates));
  char stack[STACK_SZ];
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    crate_t *from = &crates_2[in->from - 1];
    crate_t *to = &crates_2[in->to - 1];
    pop_vec(from, stack, in->nr);
    push_vec(to, stack, in->nr);
  }
  dump(crates_2, 2, NR_CRATE);
  free(crates_2);

  return 0;
}
