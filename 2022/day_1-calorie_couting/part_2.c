#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct elve {
    int calories;
};

//#include "sample.h"
#include "puzzle.h"

static struct elve elves[NR_ELVE];
static uint32_t nr_elve = 0;

static int elve_cmp(const void *a, const void *b) {
    const struct elve *e1 = (const struct elve*)a;
    const struct elve *e2 = (const struct elve*)b;

    if (e1->calories > e2->calories) {
        return -1;
    } else if (e1->calories < e2->calories) {
        return 1;
    }
    return 0;
}

static void collect_callories() {
    for (int i = 0; i < NR_LINE; ++i) {
        if (calories[i] == -1) {
            ++nr_elve;
        } else {
            elves[nr_elve].calories += calories[i];
        }
    }
}

int main(void) {
    collect_callories();
    qsort(elves, NR_ELVE, sizeof(struct elve), elve_cmp);
    printf("1:%i, 2:%i, 3:%i\n",
           elves[0].calories,
           elves[1].calories,
           elves[2].calories);
    return 0;
}
