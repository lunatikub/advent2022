#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

typedef struct input {
  const char *room;
  unsigned id;
  const char *checksum;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

#define CHECKSUM_LEN 5
#define ALPHA_SZ 26

static void process_checksum(const char *room, char *checksum) {
  unsigned max = 0;
  unsigned count[ALPHA_SZ] = { 0 };
  for (unsigned i = 0; i < strlen(room); ++i) {
    if (room[i] == '-') {
      continue;
    }
    ++count[room[i] - 'a'];
    if (count[room[i] - 'a'] > max) {
      max = count[room[i] - 'a'];
    }
  }

  unsigned idx = 0;
  while (idx != CHECKSUM_LEN) {
    for (unsigned i = 0; i < ALPHA_SZ; ++i) {
      if (count[i] == max) {
        checksum[idx] = 'a' + i;
        ++idx;
        if (idx == CHECKSUM_LEN) {
          break;
        }
      }
    }
    --max;
  }
}

static char shift(char c, unsigned n) {
  return (c + n) % 26;
}

static char* decrypt(const char *room, unsigned n) {
  char *decrypted = calloc(sizeof(char),strlen(room) + 1);
  for (unsigned i = 0; i < strlen(room); ++i) {
    if (room[i] == '-') {
      decrypted[i] = ' ';
    } else {
      decrypted[i] = shift(room[i] - 'a', n) + 'a';
    }
  }
  return decrypted;
}

int main(void) {
  unsigned sum_id = 0;
  unsigned room_id_northpole = 0;
  char checksum[CHECKSUM_LEN + 1] = {};

  for (unsigned i = 0; i < NR_INPUT; ++i) {
    const input_t *in = &inputs[i];
    process_checksum(in->room, checksum);
    if (strcmp(in->checksum, checksum) == 0) {
      sum_id += in->id;
    }
    char *decrypted = decrypt(in->room, in->id);
    if (strcmp(decrypted, "northpole object storage") == 0) {
      room_id_northpole = in->id;
    }
    free(decrypted);
  }

  printf("> part 1: %u\n", sum_id);
  printf("> part 2: %u\n", room_id_northpole);
  return 0;
}
