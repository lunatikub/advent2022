#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  const char *n;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

static char common_bit(unsigned *flags, unsigned col, bool most) {
  int b = 0;
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    if (flags != NULL && flags[i] == 1) {
      continue;
    }
    const input_t *in = &inputs[i];
    if (in->n[col] == '1') {
      ++b;
    } else if (in->n[col] == '0') {
      --b;
    }
  }
  if (most == true) {
    return b >= 0 ? '1' : '0';
  }
  return b >= 0 ? '0' : '1';
}

static unsigned flag_number(unsigned *flags, unsigned col, char bit) {
  unsigned n = 0;
  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    if (flags[i] == 1) {
      continue;
    }
    if (bit != in->n[col]) {
      flags[i] = 1;
      ++n;
    }
  }
  return n;
}

static int binstr_to_int(const char *str, unsigned len) {
  int n = 0;
  for (unsigned i = 0; i < len; ++i) {
    if (str[i] == '1')
      n |= 1 << (len - i - 1);
  }
  return n;
}

static unsigned part_1(unsigned len) {
  char *mcbs = calloc(len, sizeof(char));
  int mask = (1 << len) - 1;

  for (unsigned i = 0; i < len; ++i) {
    mcbs[i] = common_bit(NULL, i, true);
  }
  int gamma = binstr_to_int(mcbs, len);
  int epsilon = ~gamma & mask;
  free(mcbs);
  return gamma * epsilon;
}

static unsigned part_2(unsigned len) {
  unsigned oxygen = 0;
  unsigned scrubber = 0;
  unsigned nr_oxygen = NR_INPUT;
  unsigned nr_scrubber = NR_INPUT;
  unsigned *flags_scrubber = calloc(NR_INPUT, sizeof(unsigned));
  unsigned *flags_oxygen = calloc(NR_INPUT, sizeof(unsigned));

  for (unsigned i = 0; i < len; ++i) {
    if (nr_oxygen != 1) {
      char mcb = common_bit(flags_oxygen, i, true);
      nr_oxygen -= flag_number(flags_oxygen, i, mcb);
    }
    if (nr_scrubber != 1) {
      char lcb = common_bit(flags_scrubber, i, false);
      nr_scrubber -= flag_number(flags_scrubber, i, lcb);
    }
  }
  assert(nr_oxygen == 1 && nr_scrubber == 1);

  for (unsigned i = 0; i < NR_INPUT; ++i) {
    if (flags_oxygen[i] == 0) {
      assert(oxygen == 0);
      oxygen = binstr_to_int(inputs[i].n, len);
    }
    if (flags_scrubber[i] == 0) {
      assert(scrubber == 0);
      scrubber = binstr_to_int(inputs[i].n, len);
    }
  }

  free(flags_scrubber);
  free(flags_oxygen);
  return oxygen * scrubber;
}

int main(void) {
  unsigned len = strlen(inputs[0].n);
  printf("> part 1: %i\n", part_1(len));
  printf("> part 2: %u\n", part_2(len));
  return 0;
}
