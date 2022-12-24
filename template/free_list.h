  while (!SLIST_EMPTY(&list)) {
    person_t *p = SLIST_FIRST(&list);
    SLIST_REMOVE_HEAD(&list, next);
    free(p->field_1);
    free(p->field_1);
    free(p);
  }
