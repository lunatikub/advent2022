#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "filesystem.h"

static dir_t *fs_dir_new(const char *name, dir_t *parent) {
  dir_t *d = calloc(1, sizeof(*d));
  d->name = strdup(name);
  d->parent = parent;
  return d;
}

static file_t *fs_file_new(const char *name, size_t sz) {
  file_t *f = calloc(1, sizeof(*f));
  f->name = strdup(name);
  f->sz = sz;
  return f;
}

void fs_dir_add(dir_t *current, const char *name) {
  dir_t *d = fs_dir_new(name, current);
  d->next = current->head;
  current->head = d;
}

dir_t *fs_dir_find(dir_t *current, const char *name) {
  dir_t *d = current->head;
  while (d != NULL) {
    if (strcmp(d->name, name) == 0) {
      return d;
    }
    d = d->next;
  }
  return d;
}

static void fs_update_sz(dir_t *current, size_t sz) {
  while (current != NULL) {
    current->sz += sz;
    current = current->parent;
  }
}

void fs_file_add(dir_t *current, const char *name, size_t sz) {
  file_t *f = fs_file_new(name, sz);
  f->next = current->files;
  current->files = f;
  fs_update_sz(current, sz);
}


static void fs_dump_indent(uint32_t indent) {
  for (unsigned i = 0; i < indent; ++i) {
    printf(" ");
  }
}

#define INDENT_INC 2

void fs_dump(dir_t *d, uint32_t indent);

static void fs_dump_file(dir_t *d, uint32_t indent) {
  file_t *f = d->files;
  while (f != NULL) {
    fs_dump_indent(indent);
    printf("- %s (file, size=%lu)\n", f->name, f->sz);
    f = f->next;
  }
}

void fs_dump(dir_t *d, uint32_t indent) {
  if (d == NULL) {
    return;
  }
  fs_dump_indent(indent);
  printf("- %s (dir, size=%lu)\n", d->name, d->sz);
  fs_dump_file(d, indent + INDENT_INC);
  fs_dump(d->head, indent + INDENT_INC);
  if (d->next != NULL) {
    fs_dump(d->next, indent);
  }
}

static void fs_clean_dir(dir_t *d, bool root) {
  if (d == NULL) {
    return;
  }
  file_t *f = d->files;
  file_t *current;
  while (f != NULL) {
    current = f;
    f = f->next;
    free(current->name);
    free(current);
  }
  fs_clean_dir(d->head, false);
  fs_clean_dir(d->next, false);
  free(d->name);
  if (root != true) {
    free(d);
  }
}

void fs_clean(filesystem_t *fs) {
  fs_clean_dir(&fs->root, true);
}

static void fs_dir_lt(dir_t *d, size_t val, size_t *tot) {
  if (d == NULL) {
    return;
  }
  if (d->sz < val) {
    *tot += d->sz;
  }
  fs_dir_lt(d->head, val, tot);
  fs_dir_lt(d->next, val, tot);
}

size_t fs_find_dir_lt(filesystem_t *fs, size_t val) {
  size_t tot = 0;
  fs_dir_lt(&fs->root, val, &tot);
  return tot;
}

static void fs_min_dir(dir_t *d, size_t needed, dir_t **min) {
  if (d == NULL) {
    return;
  }
  if (d->sz > needed && d->sz < (*min)->sz) {
    *min = d;
  }
  fs_min_dir(d->head, needed, min);
  fs_min_dir(d->next, needed, min);
}

dir_t* fs_find_min_dir(filesystem_t *fs, size_t val) {
  dir_t *min = &fs->root;
  fs_min_dir(&fs->root, val, &min);
  return min;
}

static void path_cd_prev(char *path) {
  for (int i = strlen(path) - 2; i >= 0; --i) {
      if (path[i] == '/') {
        path[i + 1] = 0;
        break;
      }
    }
}

typedef struct context {
  char path[1024];
  dir_t *current;
  uint32_t id;
} context_t;

static void cd(filesystem_t *fs, context_t *ctx, const char *path) {
  printf("[DBG:%s] cd %s\n", ctx->path, path);

  if (strcmp(path, "/") == 0) {
    ctx->current = &fs->root;
    fs->root.name = strdup("/");
    strcpy(ctx->path, "/");
    return;
  }

  if (strcmp(path, "..") == 0) {
    ctx->current = ctx->current->parent;
    path_cd_prev(ctx->path);
    return;
  }

  ctx->current = fs_dir_find(ctx->current, path);
  assert(ctx->current != NULL);
  strcat(ctx->path, path);
  strcat(ctx->path, "/");
}

static void ls(context_t *ctx, const entry_t *entries, uint32_t nr_entry) {
  printf("[DBG:%s] ls\n", ctx->path);
   ++ctx->id;
  for (unsigned i = 0; i < nr_entry; ++i) {
    const entry_t *e = &entries[i];
    if (e->id == ctx->id) {
      if (e->type == D) {
        printf("[DBG:%s] dir add %s\n", ctx->path, e->name);
        fs_dir_add(ctx->current, e->name);
      } else if (e->type == F) {
        printf("[DBG:%s] file add %s (%lu)\n", ctx->path, e->name, e->sz);
        fs_file_add(ctx->current, e->name, e->sz);
      }
    }
  }
}

void fs_create(filesystem_t *fs,
               const command_t *cmds,
               uint32_t nr_cmd,
               const entry_t *entries,
               uint32_t nr_entry) {

  context_t ctx = { .current = &fs->root };

  for (unsigned i = 0; i < nr_cmd; ++i) {
    const command_t *c = &cmds[i];
    if (c->type == CD) {
      cd(fs, &ctx, c->path);
    } else if (c->type == LS) {
      ls(&ctx, entries, nr_entry);
    }
  }
}
