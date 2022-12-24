#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  char *name;
  char *next;    // sitting next to
  int happinnes; // happinness (gain or lose)
} input_t;

//#include "sample.h"
#include "puzzle.h"

typedef struct person {
  SLIST_ENTRY(person) next;
  unsigned id;
  char *name;
} person_t;

static SLIST_HEAD(, person) persons;
static unsigned nr_person = 0;

static void person_add(const char *name) {
  person_t *iter;
  SLIST_FOREACH(iter, &persons, next) {
    if (strcmp(iter->name, name) == 0) {
      return;
    }
  }
  iter = malloc(sizeof(*iter));
  iter->name = strdup(name);
  iter->id = nr_person++;
  SLIST_INSERT_HEAD(&persons, iter, next);
}

static void persons_free(void) {
  while (!SLIST_EMPTY(&persons)) {
    person_t *p = SLIST_FIRST(&persons);
    SLIST_REMOVE_HEAD(&persons, next);
    free(p->name);
    free(p);
  }
}

static const char *person_find_from_id(unsigned id) {
  person_t *iter;
  SLIST_FOREACH(iter, &persons, next) {
    if (iter->id == id) {
      return iter->name;
    }
  }
  return NULL;
}

static int get_happinness(const char *p1, const char *p2) {
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    if (strcmp(in->name, p1) == 0 && strcmp(in->next, p2) == 0) {
      return in->happinnes;
    }
  }
  return 0; // "me"
}

static void combination(unsigned *ids, int *max_happinnes) {
  int happinnes = 0;
  for (unsigned i = 0; i < nr_person; ++i) {
    unsigned id = ids[i];
    unsigned id_prev = (i == 0) ? ids[nr_person - 1] : ids[i - 1];
    unsigned id_next = (i == nr_person - 1) ? ids[0] : ids[i + 1];

    const char *p = person_find_from_id(id);
    const char *p_prev = person_find_from_id(id_prev);
    const char *p_next = person_find_from_id(id_next);

    happinnes += get_happinness(p, p_prev);
    happinnes += get_happinness(p, p_next);
  }
  if (happinnes > *max_happinnes) {
    *max_happinnes = happinnes;
  }
}

static void swap(unsigned *ids, unsigned src, unsigned dst) {
  unsigned tmp = ids[src];
  ids[src] = ids[dst];
  ids[dst] = tmp;
}

// build an array of ids from this list of persons
static unsigned *create_list_of_ids(void) {
  unsigned *ids = malloc(sizeof(unsigned) * nr_person);
  person_t *iter;
  unsigned i = 0;
  SLIST_FOREACH(iter, &persons, next) { ids[i++] = iter->id; }
  return ids;
}

static void permutation(unsigned *ids, unsigned l, unsigned r,
                        int *max_happinnes) {
  if (l == r) {
    combination(ids, max_happinnes);
    return;
  }

  for (unsigned i = l; i <= r; ++i) {
    swap(ids, l, i);
    permutation(ids, l + 1, r, max_happinnes);
    swap(ids, l, i);
  }
}

int main(void) {
  unsigned *ids = NULL;
  int max_happinnes;

  // Create the list of unique person
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    person_add(in->name);
    person_add(in->next);
  }

  // part_1: find the maximum happinnes from all possible
  // permutations/combinations
  max_happinnes = 0;
  ids = create_list_of_ids();
  permutation(ids, 0, nr_person - 1, &max_happinnes);
  printf("> part_1: %i\n", max_happinnes);
  free(ids);

  // part_2
  // add myself
  person_add("me");
  ids = create_list_of_ids();
  max_happinnes = 0;
  permutation(ids, 0, nr_person - 1, &max_happinnes);
  free(ids);
  printf("> part_2: %i\n", max_happinnes);

  persons_free();
  return 0;
}
