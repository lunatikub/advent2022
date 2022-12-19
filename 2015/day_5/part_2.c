#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Return true if it contains a pair of any two letters
// that appears at least twice in the string without overlapping
// Return false otherwise.
static inline bool property_1(const char *str, size_t len) {
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
static inline bool property_2(const char *str, size_t len) {
  for (size_t i = 0; i < len - 2; ++i) {
    if (str[i] == str[i + 2]) {
      return true;
    }
  }
  return false;
}

static inline bool is_nice(const char *str, size_t len) {
  return property_1(str, len) && property_2(str, len);
}

#include "puzzle.h"

int main(void) {
  static const char sample1[] = "qjhvhtzxzqqjkmpb";
  static const char sample2[] = "xxyxx";
  static const char sample3[] = "uurcxstgmygtbstg";
  static const char sample4[] = "ieodomkazucvgmuy";

  assert(is_nice(sample1, strlen(sample1)) == true);
  assert(is_nice(sample2, strlen(sample2)) == true);
  assert(is_nice(sample3, strlen(sample3)) == false);
  assert(is_nice(sample4, strlen(sample4)) == false);

  unsigned nr_nice = 0;
  for (unsigned i = 0; i < NR_STR; ++i) {
    if (is_nice(puzzle[i], strlen(puzzle[i])) == true) {
      ++nr_nice;
    }
  }
  printf("> nr_nice: %u\n", nr_nice);

  return 0;
}
