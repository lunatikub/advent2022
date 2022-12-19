#include <assert.h>
#include <openssl/md5.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static inline bool md5_00000(const unsigned char *in, size_t len) {
  unsigned char result[MD5_DIGEST_LENGTH];
  MD5(in, len, result);

  return result[0] == 0 && result[1] == 0 && (result[2] & 0xf0) == 0;
}

int main(void) {
  static const unsigned char puzzle[] = "ckczppom";

  char str[128];

  unsigned i = 1;
  while (true) {
    sprintf(str, "%s%u", puzzle, i);
    if (md5_00000((unsigned char *)str, strlen(str)) == true) {
      printf("> %u\n", i);
      break;
    }
    ++i;
    assert(i != 0); // overflow
  }

  return 0;
}
