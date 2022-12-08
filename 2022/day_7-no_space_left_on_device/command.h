#ifndef COMMAND_H_
# define COMMAND_H_

#include <stdint.h>

#define CD 1
#define LS 2

typedef struct {
    uint8_t type;
    char *path;
} command_t;

#endif /* !COMMAND_H_ */
