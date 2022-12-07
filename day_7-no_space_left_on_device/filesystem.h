#ifndef FILESYSTEM_H_
# define FILESYSTEM_H_

#include <stdint.h>
#include <stdlib.h>

#include "command.h"
#include "entry.h"

typedef struct file {
  char *name;
  size_t sz;
  struct file *next;
} file_t;

typedef struct dir {
  char *name;
  struct dir *parent;
  struct dir *head;
  struct dir *next;
  file_t *files;
  size_t sz;
} dir_t;

typedef struct filesystem {
  dir_t root;
  /* char path[1024]; */
  /* dir_t *current; */
  /* uint32_t id; */
} filesystem_t;

void fs_dir_add(dir_t *current, const char *name);
dir_t* fs_dir_find(dir_t *current, const char *name);
void fs_file_add(dir_t *current, const char *name, size_t sz);
void fs_dump(dir_t *current, uint32_t indent);
void fs_clean(filesystem_t *fs);
size_t fs_find_dir_lt(filesystem_t *fs, size_t val);
dir_t* fs_find_min_dir(filesystem_t *fs, size_t val);

void fs_create(filesystem_t *fs,
               const command_t *cmd,
               uint32_t nr_cmd,
               const entry_t *entries,
               uint32_t nr_entry);

#endif /* !FILESYSTEM_H_ */
