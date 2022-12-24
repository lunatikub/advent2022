typedef struct elt {
  SLIST_ENTRY(elt) next;
  char data[];
} elt_t;

typedef struct set {
  SLIST_HEAD(, elt) head;
  size_t nr;
  size_t sz;
} set_t;

static inline bool set_exist(set_t *set, const void *data) {
  elt_t *iter;
  SLIST_FOREACH(iter, &set->head, next) {
    if (memcmp(iter->data, data, set->sz) == 0) {
      return true;
    }
  }
  return false;
}

static inline void set_add(set_t *set, void *data) {
  if (set_exist(set, data) == true) {
    return;
  }
  elt_t *elt = calloc(1, sizeof(*elt) + set->sz);
  SLIST_INSERT_HEAD(&set->head, elt, next);
  memcpy(elt->data, data, set->sz);
  ++set->nr;
}

static inline void set_free(set_t *set) {
  while (!SLIST_EMPTY(&set->head)) {
    elt_t *iter = SLIST_FIRST(&set->head);
    SLIST_REMOVE_HEAD(&set->head, next);
    free(iter);
  }
  set->nr = 0;
}

static inline void set_init(set_t *set, size_t sz) {
  SLIST_INIT(&set->head);
  set->sz = sz;
  set->nr = 0;
}
