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

static bool start_with_00000(unsigned char *result) {
  return result[0] == 0 && result[1] == 0 && (result[2] & 0xf0) == 0;
}

#define INPUT_SZ 256
#define PWD_LEN 8

static const char mapping[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                               '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

typedef void (*part_cb)(const unsigned char *result, char *pwd,
                        unsigned *pwd_len);

/**
 * The 6th char of the hash `result` is the pwd char at the
 * next position.
 */
static void part_1_cb(const unsigned char *result, char *pwd,
                      unsigned *pwd_len) {
  char c = mapping[result[2] & 0x0f]; // 6th char of the hash
  pwd[*pwd_len] = c;
  ++(*pwd_len);
}

/**
 * The 6th char of the hash `result` is the position of the pwd char.
 * The 7th char of the hash `result` is the pwd char.
 * Position has to be valid and ignore already filled char.
 */
static void part_2_cb(const unsigned char *result, char *pwd,
                      unsigned *pwd_len) {
  int pos = result[2] & 0x0f;
  char c = mapping[(result[3] & 0xf0) >> 4];
  if (pos >= 0 && pos < PWD_LEN && pwd[pos] == 0) {
    pwd[pos] = c;
    ++(*pwd_len);
  }
}

static void find_pwd(const char *prefix, char *pwd, part_cb cb) {
  char input[INPUT_SZ];
  unsigned n = 1;
  unsigned char result[MD5_DIGEST_LENGTH];
  unsigned pwd_len = 0;

  while (pwd_len != PWD_LEN) {
    unsigned len = sprintf(input, "%s%u", prefix, n);
    MD5((unsigned char *)input, len, result);
    if (start_with_00000(result) == true) {
      cb(result, pwd, &pwd_len);
    }
    ++n;
  }
}

int main(void) {
  char pwd[PWD_LEN + 1] = {};

  find_pwd(inputs[0].str, pwd, part_1_cb);
  printf("> part 1: %s\n", pwd);

  memset(pwd, 0, PWD_LEN + 1);

  find_pwd(inputs[0].str, pwd, part_2_cb);
  printf("> part 2: %s\n", pwd);

  return 0;
}
