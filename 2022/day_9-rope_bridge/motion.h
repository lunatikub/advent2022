#ifndef MOTION_H_
# define MOTION_H_

#include <stdlib.h>

#include "coord.h"

#define R 1
#define L 2
#define U 3
#define D 4

typedef struct motion {
  uint32_t type;
  uint32_t step;
} motion_t;

static inline void head_motion(coord_t *head, uint32_t direct) {
    switch (direct) {
        case R: ++head->x; break;
        case L: --head->x; break;
        case U: --head->y; break;
        case D: ++head->y; break;
    }
}

static int normalize(int n) {
    if (n > 0) {
        return 1;
    }
    if (n < 0) {
        return -1;
    }
    return 0;
}

static void knot_motion(coord_t *prev, coord_t *current) {
    int step_x = prev->x - current->x;
    int step_y = prev->y - current->y;

    if (abs(step_x) > 1 || abs(step_y) > 1) {
        current->x += normalize(step_x);
        current->y += normalize(step_y);
    }
}

#endif /* !MOTION_H_ */
