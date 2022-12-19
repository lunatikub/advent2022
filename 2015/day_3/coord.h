#ifndef COORD_H_
#define COORD_H_

#include <stdlib.h>

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

#endif /* !COORD_H_ */
