#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef enum shape {
  rock,
  paper,
  scissors,
} shape_t;

enum shape_score {
  rock_score = 1,
  paper_score = 2,
  scissors_score = 3,
};

enum outcome {
  lost = 0,
  draw = 3,
  win = 6,
};

struct round {
    char opponent;
    char you;
};

//#include "sample.h"
#include "puzzle.h"

shape_t get_shape_opponent(char shape) {
  switch (shape) {
    case 'A': return rock;
    case 'B': return paper;
    case 'C': return scissors;
  };
  return rock;
}

shape_t get_shape_you(char shape) {
  switch (shape) {
    case 'X': return rock;
    case 'Y': return paper;
    case 'Z': return scissors;
  };
  return rock;
}

int get_shape_score(shape_t s) {
    switch (s) {
        case rock: return rock_score;
        case paper: return paper_score;
        case scissors: return scissors_score;
    }
    return rock_score;
}

// Rock defeats Scissors, Scissors defeats Paper, and Paper defeats Rock.
int get_round_score(shape_t o, shape_t y) {
    if (o == y) {
        return draw;
    }
    if (((o == rock) && (y == scissors)) ||
        ((o == scissors) && (y == paper)) ||
        ((o == paper) && (y == rock))) {
        return lost;
    }
    return win;
 }

int main(void) {
    int score = 0;
    for (int i = 0; i < NR_ROUND; ++i) {
        const struct round *r = &rounds[i];

        shape_t o = get_shape_opponent(r->opponent);
        shape_t y = get_shape_you(r->you);

        score += get_shape_score(y) + get_round_score(o, y);
    }
    printf("score:%i\n", score);
    return 0;
}
