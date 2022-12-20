#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct dist {
  char *city_1;
  char *city_2;
  unsigned n;
} dist_t;

//#include "sample.h"
#include "puzzle.h"

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

  for (unsigned i = 0; i < NR_DIST; ++i) {
    dist_t *d = &dists[i];
    if ((strcmp(d->city_1, city_1->name) == 0 &&
         strcmp(d->city_2, city_2->name) == 0) ||
        (strcmp(d->city_1, city_2->name) == 0 &&
         strcmp(d->city_2, city_1->name) == 0)) {
      return d->n;
    }
  }
  printf("> err distance");
  return 0;
}

static void get_route(unsigned *id, unsigned *shortest, unsigned *longest) {
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

static void permutation(unsigned *id, unsigned l, unsigned r,
                        unsigned *shortest, unsigned *longest) {
  if (l == r) {
    get_route(id, shortest, longest);
    return;
  }

  for (unsigned i = l; i <= r; ++i) {
    swap(id, l, i);
    permutation(id, l + 1, r, shortest, longest);
    swap(id, l, i);
  }
}

int main(void) {
  unsigned i;
  SLIST_INIT(&cities);

  // build the set of cities
  for (i = 0; i < NR_DIST; ++i) {
    lookup_create_city(dists[i].city_1);
    lookup_create_city(dists[i].city_2);
  }

  // build an array of ids from this list of cities
  unsigned *id = malloc(sizeof(*id) * nr_city);
  city_t *iter;
  i = 0;
  SLIST_FOREACH(iter, &cities, next) { id[i++] = iter->id; }

  // build all the permutations
  unsigned shortest = INT32_MAX;
  unsigned longest = 0;
  permutation(id, 0, nr_city - 1, &shortest, &longest);
  printf("> shortest: %u\n", shortest);
  printf("> longtest: %u\n", longest);

  return 0;
}
