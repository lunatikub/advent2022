#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#include "../../common/jsmn.h"

typedef struct input {
  char *json;
} input_t;

#ifdef PUZZLE
#include "puzzle.h"
#else
#include "sample.h"
#endif

static inline bool is_number(const char *str) {
  unsigned i = 0;
  if (str[0] == '-') {
    i = 1;
  }
  for (; i < strlen(str); ++i) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

static int json_deepsearch(const char *json, jsmntok_t *token, size_t count,
                           int *n);

static int json_primitve(const char *json, jsmntok_t *token, int *n) {
  char number[32];
  size_t len = token->end - token->start;
  assert(len < 32);
  strncpy(number, json + token->start, len);
  number[len] = 0;
  if (is_number(number) == true) {
    *n += atoi(number);
  }
  return 1;
}

static int json_string(const char *json, jsmntok_t *token) {
  (void)json;
  (void)token;
  return 1;
}

static int json_object(const char *json, jsmntok_t *token, size_t count,
                       int *n) {
  jsmntok_t *key;
  int j = 0;
  for (int i = 0; i < token->size; i++) {
    key = token + 1 + j;
    j += json_deepsearch(json, key, count - j, n);
    if (key->size > 0) {
      j += json_deepsearch(json, token + 1 + j, count - j, n);
    }
  }
  return j + 1;
}

static int json_array(const char *json, jsmntok_t *token, size_t count,
                      int *n) {
  int j = 0;
  for (int i = 0; i < token->size; i++) {
    j += json_deepsearch(json, token + 1 + j, count - j, n);
  }
  return j + 1;
}

static int json_deepsearch(const char *json, jsmntok_t *token, size_t count,
                           int *n) {
  if (count == 0) {
    return 0;
  }

  switch (token->type) {
  case JSMN_PRIMITIVE:
    return json_primitve(json, token, n);
  case JSMN_STRING:
    return json_string(json, token);
  case JSMN_OBJECT:
    return json_object(json, token, count, n);
  case JSMN_ARRAY:
    return json_array(json, token, count, n);
  default:
    abort();
  };
  return 0;
}

static void remove_all_object_with_red(char *json) {}

#define NR_TOKEN 5773

int main(void) {
  jsmn_parser parser;
  jsmntok_t *tokens = malloc(sizeof(jsmntok_t) * NR_TOKEN);

  const char *json = inputs[0].json;

  jsmn_init(&parser);
  int r = jsmn_parse(&parser, json, strlen(json), tokens, NR_TOKEN);
  if (r < 0) {
    printf("Failed to parse JSON: %d\n", r);
    return 1;
  }

  int n = 0;
  json_deepsearch(json, tokens, NR_TOKEN, &n);
  printf("> part 1: %i\n", n);
  free(tokens);

  return 0;
}
