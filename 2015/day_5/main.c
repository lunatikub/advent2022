#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  char *str;
} input_t;

//#include "sample.h"
#include "puzzle.h"

// Return true if it contains at least three vowels (aeiou only).
// Return false otherwise.
static bool property_1(const char *str, size_t len) {
  unsigned nr = 0;
  for (size_t i = 0; i < len; ++i) {
    if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' ||
        str[i] == 'u') {
      ++nr;
    }
  }
  return nr >= 3;
}

// Return true if it contains at least one letter that appears twice in a row.
// Return fasle otherwise.
static bool property_2(const char *str, size_t len) {
  char prev = str[0];
  for (size_t i = 1; i < len; ++i) {
    if (str[i] == prev) {
      return true;
    }
    prev = str[i];
  }
  return false;
}

// Return true if it does not contain the strings ab, cd, pq, or xy.
// Return fasle otherwise.
static bool property_3(const char *str, size_t len) {
  for (size_t i = 0; i < len - 1; ++i) {
    if ((str[i] == 'a' && str[i + 1] == 'b') ||
        (str[i] == 'c' && str[i + 1] == 'd') ||
        (str[i] == 'p' && str[i + 1] == 'q') ||
        (str[i] == 'x' && str[i + 1] == 'y')) {
      return false;
    }
  }
  return true;
}

// Return true if it contains a pair of any two letters
// that appears at least twice in the string without overlapping
// Return false otherwise.
static bool property_4(const char *str, size_t len) {
  for (size_t i = 0; i < len - 1; ++i) {
    for (size_t j = i + 2; j < len - 1; j++) {
      if (str[j] == str[i] && str[j + 1] == str[i + 1]) {
        return true;
      }
    }
  }
  return false;
}

// Return true if it contains at least one letter
// which repeats with exactly one letter between them.
// Return false otherwise.
static bool property_5(const char *str, size_t len) {
  for (size_t i = 0; i < len - 2; ++i) {
    if (str[i] == str[i + 2]) {
      return true;
    }
  }
  return false;
}

typedef bool (*property_cb)(const char *, size_t);

// A string is nice if its respects all the properties
static inline bool is_nice(const property_cb *properties, const char *str,
                           size_t len) {
  unsigned i = 0;
  while (properties[i] != NULL) {
    if (properties[i](str, len) == false) {
      return false;
    }
    ++i;
  }
  return true;
}

static const property_cb part_1_properties[] = {
    property_1,
    property_2,
    property_3,
    NULL,
};

static const property_cb part_2_properties[] = {
    property_4,
    property_5,
    NULL,
};

int main(void) {
  unsigned part_1_nr_nice = 0;
  unsigned part_2_nr_nice = 0;

  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const char *str = inputs[i].str;
    size_t len = strlen(str);
    if (is_nice(part_1_properties, str, len) == true) {
      ++part_1_nr_nice;
    }
    if (is_nice(part_2_properties, str, len) == true) {
      ++part_2_nr_nice;
    }
  }
  printf("> part 1: %u\n", part_1_nr_nice);
  printf("> part 2: %u\n", part_2_nr_nice);
  return 0;
}
