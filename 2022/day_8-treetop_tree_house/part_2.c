#include <stdio.h>
#include <stdbool.h>

//#include "sample.h"
#include "puzzle.h"

static uint32_t score_from_left(unsigned i, unsigned j) {
    uint32_t n = 0;
    for (int k = j - 1; k >= 0; --k) {
        ++n;
        if (grid[i][k] >= grid[i][j]) {
            break;
        }
    }
    return n;
}

static uint32_t score_from_right(unsigned i, unsigned j) {
    uint32_t n = 0;
    for (int k = j + 1; k < W; ++k) {
        ++n;
        if (grid[i][k] >= grid[i][j]) {
            break;
        }
    }
    return n;
}

static uint32_t score_from_top(unsigned i, unsigned j) {
    uint32_t n = 0;
    for (int k = i - 1; k >= 0; --k) {
        ++n;
        if (grid[k][j] >= grid[i][j]) {
            break;
        }
    }
    return n;
}

static uint32_t score_from_bot(unsigned i, unsigned j) {
    uint32_t n = 0;
    for (int k = i + 1; k < H; ++k) {
        ++n;
        if (grid[k][j] >= grid[i][j]) {
            break;
        }
    }
    return n;
}

static uint32_t get_max_score(void) {
    uint32_t max = 0;

    for (unsigned i = 1; i < H - 1; ++i) {
        for (unsigned j = 1; j < W - 1; ++j) {
            uint32_t score =
                score_from_bot(i, j) *
                score_from_top(i, j) *
                score_from_right(i, j) *
                score_from_left(i, j);
            if (score > max) {
                max = score;
            }
        }
    }

    return max;
}

int main(void) {
    printf("max score: %u\n", get_max_score());
    return 0;
}
