#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef enum type {
  ASSIGN,
  AND,
  OR,
  NOT,
  LSHIFT,
  RSHIFT,
} type_t;

typedef struct input {
  type_t type;
  char *in_1;
  char *in_2;
  char *out;
} input_t;

//#include "sample.h"
#include "puzzle.h"

typedef struct wire {
  uint16_t val;
  bool solved;
} wire_t;

static wire_t *wires;

static bool is_number(const char *str) {
  for (unsigned i = 0; i < strlen(str); ++i) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

static int find(const char *name) {
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    if (strcmp(in->out, name) == 0) {
      return i;
    }
  }
  return -1;
}

static uint16_t solve(const char *node) {
  if (is_number(node) == true) {
    return (uint16_t)atoi(node);
  }
  int idx = find(node);
  assert(idx >= 0);
  const input_t *in = &inputs[idx];
  wire_t *wire = &wires[idx];

  if (wire->solved == true) {
    return wire->val;
  }

  uint16_t n;
  switch (in->type) {
  case ASSIGN:
    n = solve(in->in_1);
    break;
  case AND:
    n = solve(in->in_1) & solve(in->in_2);
    break;
  case OR:
    n = solve(in->in_1) | solve(in->in_2);
    break;
  case NOT:
    n = ~solve(in->in_1);
    break;
  case LSHIFT:
    n = solve(in->in_1) << solve(in->in_2);
    break;
  case RSHIFT:
    n = solve(in->in_1) >> solve(in->in_2);
    break;
  default:
    abort();
  }

  wire->solved = true;
  wire->val = n;
  return n;
}

static void wires_init(void) {
  wires = malloc(sizeof(wire_t) * NR_INPUT);
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    wires[i].solved = false;
    wires[i].val = 0;
  }
}

int main(void) {
  uint16_t a;

  wires_init();
  {
    a = solve("a");
    printf("> part 1: %u\n", a);
  }
  free(wires);

  wires_init();
  {
    // override wire "b" with signal "a"
    int idx_b = find("b");
    assert(idx_b >= 0);
    wires[idx_b].val = a;
    wires[idx_b].solved = true;
    a = solve("a");
    printf("> part 2: %u\n", a);
  }
  free(wires);
  return 0;
}
