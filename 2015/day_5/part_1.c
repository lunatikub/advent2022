#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Return true if it contains at least three vowels (aeiou only).
// Return false otherwise.
static inline bool property_1(const char *str, size_t len) {
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
static inline bool property_2(const char *str, size_t len) {
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
static inline bool property_3(const char *str, size_t len) {
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

static inline bool is_nice(const char *str, size_t len) {
  return property_1(str, len) && property_2(str, len) && property_3(str, len);
}

#include "puzzle.h"

int main(void) {
  static const char sample1[] = "ugknbfddgicrmopn";
  static const char sample2[] = "aaa";
  static const char sample3[] = "jchzalrnumimnmhp";
  static const char sample4[] = "haegwjzuvuyypxyu";
  static const char sample5[] = "dvszwmarrgswjxmb";

  assert(is_nice(sample1, strlen(sample1)) == true);
  assert(is_nice(sample2, strlen(sample2)) == true);
  assert(is_nice(sample3, strlen(sample3)) == false);
  assert(is_nice(sample4, strlen(sample4)) == false);
  assert(is_nice(sample5, strlen(sample5)) == false);

  unsigned nr_nice = 0;
  for (unsigned i = 0; i < NR_STR; ++i) {
    if (is_nice(puzzle[i], strlen(puzzle[i])) == true) {
      ++nr_nice;
    }
  }
  printf("> nr_nice: %u\n", nr_nice);

  return 0;
}
