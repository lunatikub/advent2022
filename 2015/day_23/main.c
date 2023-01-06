#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

// Available instructions
#define HLF 1
#define TPL 2
#define INC 3
#define JMP 4
#define JIE 5
#define JIO 6

typedef struct input {
  int addr; // addr
  int type; // instruction type
  char reg; // register
  int offset;
} input_t;

#ifndef PUZZLE
#include "sample.h"
#else
#include "puzzle.h"
#endif

static int a;
static int b;

static int get(char reg) {
  if (reg == 'a') {
    return a;
  }
  if (reg == 'b') {
    return b;
  }
  abort();
}

static void set(char reg, int v) {
  if (reg == 'a') {
    a = v;
  } else if (reg == 'b'){
    b = v;
  } else {
    abort();
  }
}

static int hlf(const input_t *inst) {
  int v = get(inst->reg);
  set(inst->reg, v / 2);
  return inst->addr + 1;
}

static int tpl(const input_t *inst) {
  int v = get(inst->reg);
  set(inst->reg, v * 3);
  return inst->addr + 1;
}

static int inc(const input_t *inst) {
  int v = get(inst->reg);
  set(inst->reg, v + 1);
  return inst->addr + 1;
}

static int jmp(const input_t *inst) {
  return inst->addr + inst->offset;
}

static int jie(const input_t *inst) {
  int v = get(inst->reg);
  if (v % 2 == 0) {
    return inst->addr + inst->offset;
  }
  return inst->addr + 1;
}

static int jio(const input_t *inst) {
  int v = get(inst->reg);
  if (v == 1) {
    return inst->addr + inst->offset;
  }
  return inst->addr + 1;
}

static int exec_instruction(const input_t *inst) {
  if (inst->type == HLF) {
    return hlf(inst);
  }
  if (inst->type == TPL) {
    return tpl(inst);
  }
  if (inst->type == INC) {
    return inc(inst);
  }
  if (inst->type == JMP) {
    return jmp(inst);
  }
  if (inst->type == JIE) {
    return jie(inst);
  }
  if (inst->type == JIO) {
    return jio(inst);
  }
  abort();
}

static void exec_program(int start_a, int start_b) {
  a = start_a;
  b = start_b;
  int next_inst = 0;
  while (next_inst != -1 && next_inst < NR_INPUT) {
    const input_t *inst = &inputs[next_inst];
    next_inst = exec_instruction(inst);
  }
}

int main(void) {
  exec_program(0, 0);
  printf("> part 1: %u\n", b);
  exec_program(1, 0);
  printf("> part 2: %u\n", b);
  return 0;
}
