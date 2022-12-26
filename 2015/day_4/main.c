#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include <openssl/md5.h>

typedef struct input {
  char *str;
} input_t;

#ifdef PUZZLE
#include "puzzle.h"
#else
#include "sample.h"
#endif

static bool start_with_0(unsigned char *result, unsigned nr_zero) {
  if (nr_zero == 5) {
    return result[0] == 0 && result[1] == 0 && (result[2] & 0xf0) == 0;
  }
  if (nr_zero == 6) {
    return result[0] == 0 && result[1] == 0 && result[2] == 0;
  }
  abort();
  return false;
}

#define INPUT_SZ 256

static unsigned find_md5_start_with_0(const char *prefix, unsigned nr_zero) {
  char input[INPUT_SZ];
  unsigned n = 1;
  unsigned char result[MD5_DIGEST_LENGTH];

  while (n != 0) {
    unsigned len = sprintf(input, "%s%u", prefix, n);
    assert(len < INPUT_SZ);
    MD5((unsigned char *)input, len, result);
    if (start_with_0(result, nr_zero) == true) {
      return n;
    }
    ++n;
  }
  abort(); // overflow
  return 0;
}

int main(void) {
  unsigned n;

  // part 1
  n = find_md5_start_with_0(inputs[0].str, 5);
  printf("> part 1: %u\n", n);

  // part 2
  n = find_md5_start_with_0(inputs[0].str, 6);
  printf("> part 2: %u\n", n);

  return 0;
}
