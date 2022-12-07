#include <string.h>
#include <stdio.h>

//#include "sample.h"
#include "puzzle.h"

#include "filesystem.h"

int main(void) {
  filesystem_t fs;
  fs_create(&fs, cmds, NR_CMD, entries, NR_ENTRY);
  printf("\n");
  fs_dump(&fs.root, 0);
  printf("\n<<%lu>>\n", fs_find_dir_lt(&fs, 100000));
  fs_clean(&fs);
  return 0;
}
