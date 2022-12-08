#ifndef CRATE_H_
# define CRATE_H_

#define STACK_SZ 255

typedef struct crate {
    char stack[STACK_SZ];
    unsigned nr;
    unsigned id;
} crate_t;

void crate_push(crate_t *c, char val);
char crate_pop(crate_t *c);
void crate_result(const crate_t *c, unsigned nr);
void crate_dump(const crate_t *c);
void crate_dump_all(const crate_t *c, unsigned nr);

#endif /* !CRATE_H_ */
