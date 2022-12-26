#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  const char *name;
  unsigned speed; // speed in km/s
  unsigned fly;   // number of seconds it can fly
  unsigned rest;  // number of seconds it has to rest
} input_t;

#ifdef PUZZLE
#include "puzzle.h"
#else
#include "sample.h"
#endif

typedef struct reindeer {
  unsigned idx;   // input index
  bool flying;    // true: flying, false: resting
  unsigned start; // number of seconds starting flying or resting
  unsigned kms;   // number of kms gone
  unsigned score;
} reindeer_t;

static reindeer_t *reindeers;

#define NR_SECONDS 2503

static void reindeer_init(reindeer_t *r, unsigned idx) {
  r->idx = idx;
  r->flying = true; // start by flying
  r->start = 0;
  r->kms = 0;
  r->score = 0;
}

static void flying(reindeer_t *r) {
  const input_t *in = &inputs[r->idx];
  r->kms += in->speed;
  r->start++;
  if (r->start == in->fly) {
    r->flying = false;
    r->start = 0;
  }
}

static void resting(reindeer_t *r) {
  const input_t *in = &inputs[r->idx];
  r->start++;
  if (r->start == in->rest) {
    r->flying = true;
    r->start = 0;
  }
}

// 1 second step
static void step(void) {
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    reindeer_t *r = &reindeers[i];
    if (r->flying == true) {
      flying(r);
    } else {
      resting(r);
    }
  }
}

static unsigned max_score_get(void) {
  unsigned max = 0;
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    reindeer_t *r = &reindeers[i];
    if (r->score > max) {
      max = r->score;
    }
  }
  return max;
}

static unsigned max_kms_get(void) {
  unsigned max = 0;
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    reindeer_t *r = &reindeers[i];
    if (r->kms > max) {
      max = r->kms;
    }
  }
  return max;
}

static void assign_point(void) {
  unsigned max = max_kms_get();
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    reindeer_t *r = &reindeers[i];
    if (r->kms == max) {
      r->score++;
    }
  }
}

int main(void) {
  // create and init the array of reindeers
  reindeers = calloc(NR_INPUT, sizeof(reindeer_t));
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    reindeer_init(&reindeers[i], i);
  }

  for (unsigned s = 0; s < NR_SECONDS; ++s) {
    step();
    assign_point();
  }
  printf("> part 1: %u\n", max_kms_get());
  printf("> part 2: %u\n", max_score_get());

  free(reindeers);
  return 0;
}
