#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../common/number.h"

typedef enum type {
  ASSIGN,
  AND,
  OR,
  NOT,
  LSHIFT,
  RSHIFT,
} type_t;

typedef struct wire {
  type_t type;
  char *in_1;
  char *in_2;
  char *out;
  uint16_t val;
  bool solved;
} wire_t;

//#include "sample.h"
#include "puzzle.h"

static wire_t *find(const char *name) {
  wire_t *wire;
  for (unsigned i = 0; i < NR_WIRE; ++i) {
    wire = &wires[i];
    if (strcmp(wire->out, name) == 0) {
      return wire;
    }
  }
  return NULL;
}

static uint16_t solve(const char *node) {
  if (is_number(node) == true) {
    return (uint16_t)atoi(node);
  }
  wire_t *wire = find(node);
  assert(wire != NULL);

  if (wire->solved == true) {
    return wire->val;
  }

  uint16_t n;
  switch (wire->type) {
  case ASSIGN:
    n = solve(wire->in_1);
    break;
  case AND:
    n = solve(wire->in_1) & solve(wire->in_2);
    break;
  case OR:
    n = solve(wire->in_1) | solve(wire->in_2);
    break;
  case NOT:
    n = ~solve(wire->in_1);
    break;
  case LSHIFT:
    n = solve(wire->in_1) << solve(wire->in_2);
    break;
  case RSHIFT:
    n = solve(wire->in_1) >> solve(wire->in_2);
    break;
  default:
    abort();
  }

  wire->solved = true;
  wire->val = n;
  return n;
}

int main(void) {
  uint16_t a = solve("a");
  printf("[part_1] solve(\"%s\"): %u\n", "a", a);

  // reset all wires
  for (unsigned i = 0; i < NR_WIRE; ++i) {
    wire_t *w = &wires[i];
    w->val = 0;
    w->solved = false;
  }

  // override wire "b" with signal "a"
  wire_t *b = find("b");
  assert(b != NULL);
  b->val = a;
  b->solved = true;

  a = solve("a");
  printf("[part_2] solve(\"%s\"): %u\n", "a", a);

  return 0;
}
