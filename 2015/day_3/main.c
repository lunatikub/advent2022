#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  char *str;
} input_t;

#ifdef PUZZLE
#include "puzzle.h"
#else
#include "sample.h"
#endif

typedef struct coord {
  int x;
  int y;
} coord_t;

static inline void coord_update(coord_t *coord, char move) {
  switch (move) {
  case '>':
    coord->x++;
    break;
  case '<':
    coord->x--;
    break;
  case '^':
    coord->y++;
    break;
  case 'v':
    coord->y--;
    break;
  default:
    abort();
  };
}

typedef struct elt {
  SLIST_ENTRY(elt) next;
  char data[];
} elt_t;

typedef struct set {
  SLIST_HEAD(, elt) head;
  size_t nr;
  size_t sz;
} set_t;

static inline bool set_exist(set_t *set, const void *data) {
  elt_t *iter;
  SLIST_FOREACH(iter, &set->head, next) {
    if (memcmp(iter->data, data, set->sz) == 0) {
      return true;
    }
  }
  return false;
}

static inline void set_add(set_t *set, void *data) {
  if (set_exist(set, data) == true) {
    return;
  }
  elt_t *elt = calloc(1, sizeof(*elt) + set->sz);
  SLIST_INSERT_HEAD(&set->head, elt, next);
  memcpy(elt->data, data, set->sz);
  ++set->nr;
}

static inline void set_free(set_t *set) {
  while (!SLIST_EMPTY(&set->head)) {
    elt_t *iter = SLIST_FIRST(&set->head);
    SLIST_REMOVE_HEAD(&set->head, next);
    free(iter);
  }
  set->nr = 0;
}

static inline void set_init(set_t *set, size_t sz) {
  SLIST_INIT(&set->head);
  set->sz = sz;
  set->nr = 0;
}

static void count_house(const char *in) {
  coord_t santa_1 = {0, 0};
  coord_t santa_2 = {0, 0};
  coord_t robot = {0, 0};
  unsigned n = 0;
  set_t part_1;
  set_t part_2;

  set_init(&part_1, sizeof(coord_t));
  set_add(&part_1, &santa_1);

  set_init(&part_2, sizeof(coord_t));
  set_add(&part_2, &santa_2);

  for (unsigned i = 0; i < strlen(in); ++i) {
    // part 1
    coord_update(&santa_1, in[i]);
    set_add(&part_1, &santa_1);

    // part 2
    coord_t *c = ((n++ % 2) == 0) ? &santa_2 : &robot;
    coord_update(c, in[i]);
    set_add(&part_2, c);
  }

  printf("> part 1: %lu\n", part_1.nr);
  printf("> part 2: %lu\n", part_2.nr);
  set_free(&part_1);
  set_free(&part_2);
}

int main(void) {
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    count_house(in->str);
  }

  return 0;
}
