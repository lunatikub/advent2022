#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/*
** Rock defeats Scissors
** Scissors defeats Paper
** Paper defeats Rock
*/

typedef enum shape {
  rock = 1,
  paper = 2,
  scissors = 3,
} shape_t;

enum score_end {
  lost = 0,
  draw = 3,
  win = 6,
};

struct round {
    char opponent;
    char me;
};

//#include "sample.h"
#include "puzzle.h"

shape_t get_shape(char shape) {
  switch (shape) {
    case 'A': return rock;
    case 'B': return paper;
    case 'C': return scissors;
  };
  return rock;
}

/*
** X means me need to lose,
** Y means me need to end the round in a draw,
** and Z means me need to win.
*/
int get_round_score(char opp, char me) {
  shape_t opp_shape = get_shape(opp);
  switch (me) {
    case 'X':
      switch (opp_shape) {
        case rock: return scissors + lost;
        case paper: return rock + lost;
        case scissors: return paper + lost;
      };
    case 'Y':
      return opp_shape + draw;
    case 'Z':
      switch (opp_shape) {
        case rock: return paper + win;
        case paper: return scissors + win;
        case scissors: return rock + win;
      };
  };
  return 0;
}

int main(void) {
    int score = 0;
    for (int i = 0; i < NR_ROUND; ++i) {
        const struct round *r = &rounds[i];
        score += get_round_score(r->opponent, r->me);
    }
    printf("score:%i\n", score);
    return 0;
}
