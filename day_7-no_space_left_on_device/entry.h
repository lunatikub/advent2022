#ifndef ENTRY_H_
# define ENTRY_H_

#include <stdlib.h>
#include <stdint.h>

#define F 1 // file
#define D 2 // dir

typedef struct {
    uint32_t id;
    uint8_t type;
    char *name;
    size_t sz;
} entry_t;

#endif /* !ENTRY_H_ */
