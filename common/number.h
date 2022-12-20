#ifndef NUMBER_H_
#define NUMBER_H_

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

static inline bool is_number(const char *str) {
  for (unsigned i = 0; i < strlen(str); ++i) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

#endif /* !NUMBER_H_ */
