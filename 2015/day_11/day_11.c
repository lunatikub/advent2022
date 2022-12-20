#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define WORD_LEN 3
#define NR_WORD 15

static const char words[NR_WORD][WORD_LEN] = {
    "abc", "bcd", "cde", "def", "efg", "fgh", "pqr", "qrs",
    "rst", "stu", "tuv", "uvw", "vwx", "wxy", "xyz"};

/* Passwords must include one increasing straight of at least three letters,
 * like abc, bcd, cde, and so on, up to xyz. They cannot skip letters; abd
 * doesn't count.
 */
static bool rule_1(const char *str, unsigned len) {
  for (unsigned i = 0; i <= len - WORD_LEN; ++i) {
    for (unsigned j = 0; j < NR_WORD; ++j) {
      if (strncmp(&str[i], words[j], WORD_LEN) == 0) {
        return true;
      }
    }
  }
  return false;
}

/* Passwords may not contain the letters i, o, or l, as these letters can be
 * mistaken for other characters and are therefore confusing.
 */
static bool rule_2(const char *str, unsigned len) {
  for (unsigned i = 0; i < len; ++i) {
    if (str[i] == 'l' || str[i] == 'i' || str[i] == 'o') {
      return false;
    }
  }
  return true;
}

/* Passwords must contain at least two different, non-overlapping pairs of
 * letters, like aa, bb, or zz.
 */
static bool rule_3(const char *str, unsigned len) {
  unsigned a =
      strlen(str) + 1; // index of the first pairs of letters in the string
  unsigned b = 0;      // index of the last paires of letters in the string
  unsigned i;
  for (i = 0; i < len - 1; ++i) {
    if (str[i] == str[i + 1]) {
      a = i;
      break;
    }
  }
  for (i = len - 1; i >= 1; --i) {
    if (str[i] == str[i - 1]) {
      b = i - 1;
      break;
    }
  }
  return a + 1 < b; // not overlapping
}

// Incrementing is just like counting with numbers: xx, xy, xz, ya, yb, and so
// on. Increase the rightmost letter one step; if it was z, it wraps around to
// a, and repeat with the next letter to the left until one doesn't wrap around.
void inc(char *str, unsigned n) {
  if (str[n] == 'z') {
    str[n] = 'a';
    if (n > 0) {
      inc(str, n - 1);
    }
  } else {
    str[n] = (char)(str[n] + 1);
  }
}

void next_pwd(char *password, unsigned len) {
  while (true) {
    if (rule_1(password, len) == true && rule_2(password, len) == true &&
        rule_3(password, len) == true) {
      break;
    }
    inc(password, len - 1);
  }
}

int main(void) {
  char password[] = "hxbxwxba";
  unsigned len = strlen(password);

  next_pwd(password, len);
  printf("> part_1: %s\n", password);

  inc(password, len - 1);
  next_pwd(password, len);
  printf("> part_2: %s\n", password);

  return 0;
}
