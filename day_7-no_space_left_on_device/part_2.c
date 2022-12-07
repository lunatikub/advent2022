#include <assert.h>
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

  size_t tot = 70000000;
  size_t update = 30000000;
  size_t unused = tot - fs.root.sz;
  size_t needed = update - unused;

  printf("\n");
  printf("unused size: %lu\n", unused);
  printf("needed size: %lu\n", needed);

  dir_t *min = fs_find_min_dir(&fs, needed);
  printf("min: (%s) (%lu)\n", min->name, min->sz);

  fs_clean(&fs);
  return 0;
}
