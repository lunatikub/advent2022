#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  char opponent;
  char me;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

typedef enum shape {
  rock = 1,
  paper,
  scissors,
} shape_t;

#define LOST 0
#define DRAW 3
#define WIN 6

shape_t shape_opponent_get(char shape) {
  switch (shape) {
  case 'A':
    return rock;
  case 'B':
    return paper;
  case 'C':
    return scissors;
  };
  abort();
}

shape_t shape_me_get(char shape) {
  switch (shape) {
  case 'X':
    return rock;
  case 'Y':
    return paper;
  case 'Z':
    return scissors;
  };
  abort();
}

int shape_score_get(shape_t s) {
  switch (s) {
  case rock:
    return 1;
  case paper:
    return 2;
  case scissors:
    return 3;
  }
  abort();
}

int round_score_get(shape_t o, shape_t y) {
  if (o == y) {
    return DRAW;
  }
  if (((o == rock) && (y == scissors)) || ((o == scissors) && (y == paper)) ||
      ((o == paper) && (y == rock))) {
    return LOST;
  }
  return WIN;
}

/*
** X means me need to lose,
** Y means me need to end the round in a draw,
** and Z means me need to win.
*/
int round_score_strategy_get(char opp, char me) {
  shape_t so = shape_opponent_get(opp);
  switch (me) {
  case 'X':
    if (so == rock)
      return scissors + LOST;
    else if (so == paper)
      return rock + LOST;
    return paper + LOST;
  case 'Y':
    return so + DRAW;
  case 'Z':
    if (so == rock)
      return paper + WIN;
    else if (so == paper)
      return scissors + WIN;
    return rock + WIN;
  };
  abort();
}

int main(void) {
  unsigned basic_score = 0;
  unsigned strategy_score = 0;
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    shape_t so = shape_opponent_get(in->opponent);
    shape_t sm = shape_me_get(in->me);
    basic_score += shape_score_get(sm) + round_score_get(so, sm);
    strategy_score += round_score_strategy_get(in->opponent, in->me);
  }
  printf("> part 1: %u\n", basic_score);
  printf("> part 2: %u\n", strategy_score);
  return 0;
}
