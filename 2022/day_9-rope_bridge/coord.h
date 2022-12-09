#ifndef COORD_H_
# define COORD_H_

#include <sys/queue.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct coord {
    SLIST_ENTRY(coord) next;
    int x;
    int y;
} coord_t;

typedef struct list_coord {
    SLIST_HEAD(, coord) head;
    uint32_t nr;
} list_coord_t;

static inline bool list_coord_exist(list_coord_t *l, coord_t *c) {
    coord_t *iter;
    SLIST_FOREACH(iter, &l->head, next) {
        if (iter->x == c->x && iter->y == c->y) {
            return true;
        }
    }
    return false;
}

static inline void list_coord_add(list_coord_t *l, coord_t *c) {
    coord_t *new_c = calloc(1, sizeof(*new_c));
    new_c->x = c->x;
    new_c->y = c->y;
    SLIST_INSERT_HEAD(&l->head, new_c, next);
    ++l->nr;
}

#endif /* !COORD_H_ */
