#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  const char *city_1;
  const char *city_2;
  unsigned distance;
} input_t;

#ifdef PUZZLE
#include "puzzle.h"
#else
#include "sample.h"
#endif

typedef struct city {
  SLIST_ENTRY(city) next;
  unsigned id;
  char *name;
} city_t;

static unsigned nr_city = 0;
SLIST_HEAD(, city) cities;

static city_t *find_city_by_name(const char *name) {
  city_t *iter;
  SLIST_FOREACH(iter, &cities, next) {
    if (strcmp(iter->name, name) == 0) {
      return iter;
    }
  }
  return NULL;
}

static city_t *find_city_by_id(unsigned id) {
  city_t *iter;
  SLIST_FOREACH(iter, &cities, next) {
    if (iter->id == id) {
      return iter;
    }
  }
  return NULL;
}

static void lookup_create_city(const char *name) {
  if (find_city_by_name(name) == NULL) {
    city_t *c = malloc(sizeof(*c));
    c->name = strdup(name);
    c->id = nr_city++;
    SLIST_INSERT_HEAD(&cities, c, next);
  }
}

static void swap(unsigned *id, unsigned src, unsigned dst) {
  unsigned tmp = id[src];
  id[src] = id[dst];
  id[dst] = tmp;
}

static unsigned get_distance(unsigned id_1, unsigned id_2) {
  city_t *city_1 = find_city_by_id(id_1);
  city_t *city_2 = find_city_by_id(id_2);

  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    if ((strcmp(in->city_1, city_1->name) == 0 &&
         strcmp(in->city_2, city_2->name) == 0) ||
        (strcmp(in->city_1, city_2->name) == 0 &&
         strcmp(in->city_2, city_1->name) == 0)) {
      return in->distance;
    }
  }
  abort();
  return 0;
}

static void permutation(unsigned *id, unsigned *shortest, unsigned *longest) {
  unsigned route = 0;
  for (unsigned i = 0; i < nr_city - 1; ++i) {
    route += get_distance(id[i], id[i + 1]);
  }
  if (route < *shortest) {
    *shortest = route;
  }
  if (route > *longest) {
    *longest = route;
  }
}

static void permutations(unsigned *id, unsigned l, unsigned r,
                         unsigned *shortest, unsigned *longest) {
  if (l == r) {
    permutation(id, shortest, longest);
    return;
  }

  for (unsigned i = l; i <= r; ++i) {
    swap(id, l, i);
    permutations(id, l + 1, r, shortest, longest);
    swap(id, l, i);
  }
}

int main(void) {
  unsigned i;
  SLIST_INIT(&cities);

  // build the set of cities
  for (i = 0; i < NR_INPUT; ++i) {
    lookup_create_city(inputs[i].city_1);
    lookup_create_city(inputs[i].city_2);
  }

  // build an array of ids from this list of cities
  unsigned *id = malloc(sizeof(*id) * nr_city);
  city_t *iter;
  i = 0;
  SLIST_FOREACH(iter, &cities, next) { id[i++] = iter->id; }

  // build all the permutations
  unsigned shortest = INT32_MAX;
  unsigned longest = 0;
  permutations(id, 0, nr_city - 1, &shortest, &longest);
  printf("> part 1: %u\n", shortest);
  printf("> part 2: %u\n", longest);

  return 0;
}
