#include <stdio.h>

#include "coord.h"
#include "motion.h"

//#include "sample.h"
//#include "sample2.h"
#include "puzzle.h"

int main(void) {
    coord_t head = {};
    coord_t tail = {};
    list_coord_t l_coord = { .nr = 0 };
    SLIST_INIT(&l_coord.head);

    for (unsigned i = 0; i < NR_MOTION; ++i) {
        const motion_t *m = &motions[i];

        for (unsigned j = 0; j < m->step; ++j) {
            head_motion(&head, m->type);
            knot_motion(&head, &tail);
            if (list_coord_exist(&l_coord, &tail) == false) {
                list_coord_add(&l_coord, &tail);
            }
        }
    }

    printf("%u\n", l_coord.nr);
    return 0;
}
