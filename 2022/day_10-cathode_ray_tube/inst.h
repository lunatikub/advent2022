#ifndef INST_H_
#define INST_H_

enum {
  INST_ADDX,
  INST_NOOP,
};

typedef struct inst {
  int type;
  int val;
} inst_t;

#endif // INST_H_
