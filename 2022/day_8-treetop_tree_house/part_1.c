#include <stdio.h>
#include <stdbool.h>

//#include "sample.h"
#include "puzzle.h"

static uint32_t count_border_tree(void) {
    return W * 2 + H * 2 - 4;
}

static bool is_visible_from_left(unsigned i, unsigned j) {
    for (unsigned k = 0; k < j; ++k) {
        if (grid[i][k] >= grid[i][j]) {
            return false;
        }
    }
    return true;
}

static bool is_visible_from_right(unsigned i, unsigned j) {
    for (unsigned k = W - 1; k > j; --k) {
        if (grid[i][k] >= grid[i][j]) {
            return false;
        }
    }
    return true;
}

static bool is_visible_from_top(unsigned i, unsigned j) {
    for (unsigned k = 0; k < i; ++k) {
        if (grid[k][j] >= grid[i][j]) {
            return false;
        }
    }
    return true;
}

static bool is_visible_from_bot(unsigned i, unsigned j) {
    for (unsigned k = H - 1; k > i; --k) {
        if (grid[k][j] >= grid[i][j]) {
            return false;
        }
    }
    return true;
}

static uint32_t count_inside_tree(void) {
    uint32_t nr = 0;

    for (unsigned i = 1; i < H - 1; ++i) {
        for (unsigned j = 1; j < W - 1; ++j) {
            if (is_visible_from_bot(i, j) == true ||
                is_visible_from_top(i, j) ||
                is_visible_from_right(i, j) ||
                is_visible_from_left(i, j)) {
                ++nr;
            }
        }
    }

    return nr;
}

int main(void) {
    uint32_t nr_border;
    uint32_t nr_inside;
    nr_border = count_border_tree();
    printf("border nr_tree: %u\n", nr_border);
    nr_inside = count_inside_tree();
    printf("inside nr_tree: %u\n", nr_inside);
    printf("tot nr_tree:    %u\n", nr_inside + nr_border);
    return 0;
}
