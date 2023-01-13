#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  const char *from;
  const char *to;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

typedef struct molecule {
  SLIST_ENTRY(molecule) next;
  char *name;
} molecule_t;

static SLIST_HEAD(, molecule) molecules;
static unsigned nr = 0;

static molecule_t* find(const char *name) {
  molecule_t *iter;
  SLIST_FOREACH(iter, &molecules, next) {
    if (strcmp(iter->name, name) == 0) {
      return iter;
    }
  }
  return NULL;
}

static void add(char *name) {
  if (find(name) != NULL) {
    return;
  }
  molecule_t *new_molecule = malloc(sizeof(molecule_t));
  new_molecule->name = name;
  SLIST_INSERT_HEAD(&molecules, new_molecule, next);
  ++nr;
}

static void new_molecule(const char *base, unsigned base_len, const char *to, unsigned idx, unsigned from_len) {
  unsigned to_len = strlen(to);
  char *molecule = calloc(sizeof(char), base_len + to_len);
  unsigned j = 0;
  unsigned i;

  for (i = 0; i < idx; ++i) {
    molecule[j++] = base[i];
  }
  for (i = 0; i < to_len; ++i) {
    molecule[j++] = to[i];
  }
  for (i = idx + from_len; i < base_len; ++i) {
    molecule[j++] = base[i];
  }
  molecule[j] = '\0';
  printf("molecule: %s\n", molecule);
  add(molecule);
}

static unsigned build_molecules(const char *base, unsigned len, const char *from, const char *to) {
  unsigned from_len = strlen(from);
  for (unsigned i = 0; i < len + 1 - from_len; ++i) {
    if (strncmp(&base[i], from, from_len) == 0) {
      new_molecule(base, len, to, i, from_len);
    }
  }
  return 0;
}

int main(void) {

  SLIST_INIT(&molecules);
  unsigned base_len = strlen(base_molecule);

  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    printf("trans: %s -> %s\n", in->from, in->to);
    build_molecules(base_molecule, base_len, in->from, in->to);
  }
  printf("> part 1: %u\n", nr);
  printf("> part 2: %u\n", 0);
  (void)add;
  return 0;
}

// 603 >>
