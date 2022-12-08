#ifndef SAMPLE_H_
# define SAMPLE_H_

#include "command.h"
#include "entry.h"

static const command_t cmds[] = {
  { CD, "/" },
  { LS, NULL },
  { CD, "a" },
  { LS, NULL },
  { CD, "e" },
  { LS, NULL },
  { CD, ".." },
  { CD, ".." },
  { CD, "d" },
  { LS, NULL },
};

#define NR_CMD 10

static const entry_t entries[] = {
  { 1, D, "a", 0 },
  { 1, F, "b.txt", 14848514 },
  { 1, F, "c.dat", 8504156 },
  { 1, D, "d", 0 },
  { 2, D, "e", 0 },
  { 2, F, "f", 29116 },
  { 2, F, "g", 2557 },
  { 2, F, "h.lst", 62596 },
  { 3, F, "i", 584 },
  { 4, F, "j", 4060174 },
  { 4, F, "d.log", 8033020 },
  { 4, F, "d.ext", 5626152 },
  { 4, F, "k", 7214296 },
};

#define NR_ENTRY 13

#endif /* !SAMPLE_H_ */
