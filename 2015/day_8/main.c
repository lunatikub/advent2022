#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  const char *str;
} input_t;

//#include "sample.h"
#include "puzzle.h"

// '\"' have been replaced by '@D'
// '\\' have been replaced by '@B'
// '\x27' have been replaced by '@X27'
static inline void process(const char *str, unsigned len, unsigned *nr_char,
                           unsigned *nr_encoded) {
  for (unsigned i = 0; i < len; ++i) {
    if (str[i] == '@') {
      if (str[i + 1] == 'D' || str[i + 1] == 'B') {
        *nr_encoded += 2;
        ++i;
      } else if (str[i + 1] == 'X') {
        i += 3;
        *nr_encoded += 1;
      } else {
        abort();
      }
    }
    (*nr_char)++;
  }
}

int main(void) {
  unsigned tot_nr_code = 0;
  unsigned tot_nr_char = 0;
  unsigned tot_nr_code_encoded = 0;

  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const char *str = inputs[i].str;

    unsigned len = strlen(str);
    unsigned nr_char = 0;
    unsigned nr_encoded = 0;

    process(str, len, &nr_char, &nr_encoded);

    tot_nr_code += len + 2; /* "string" */
    tot_nr_char += nr_char;
    tot_nr_code_encoded += nr_encoded + len + 6; /* "\"string\"" */
  }

  printf("> part_1: %u\n", tot_nr_code - tot_nr_char);
  printf("> part_2: %u\n", tot_nr_code_encoded - tot_nr_code);
  return 0;
}
