#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 5000000

static unsigned count(char *in, unsigned in_len, unsigned i) {
  unsigned count = 1;
  while (i < in_len - 1 && in[i] == in[i + count]) {
    ++count;
  }
  return count;
}

static void concat(char *out, char c, unsigned n) {
  char tmp[STR_LEN];
  unsigned ret = snprintf(tmp, STR_LEN, "%u%c", n, c);
  assert(ret < STR_LEN);
  assert(strlen(out) + ret < STR_LEN);
  strcat(out, tmp);
}

static void seq(char *in, unsigned len, char *out) {
  for (unsigned i = 0; i < len; ++i) {
    unsigned n = count(in, len, i);
    concat(out, in[i], n);
    i += n - 1;
  }
}

#define PART_1 40
#define PART_2 50

int main(void) {
  char *in = calloc(1, STR_LEN);
  char *out = calloc(1, STR_LEN);

  strcpy(in, "1113222113");

  for (unsigned i = 0; i < 50; ++i) {
    seq(in, strlen(in), out);
    strcpy(in, out);
    memset(out, 0, STR_LEN);
    if (i == PART_1 - 1) {
      printf("> part 1:%lu\n", strlen(in));
    }
  }
  printf("> part 2:%lu\n", strlen(in));

  free(in);
  free(out);
  return 0;
}
