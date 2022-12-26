static void permutation(unsigned *ids) {
  for (unsigned i = 0; i < nr_ids; ++i) {
    printf("%u ", ids[i]);
  }
  printf("\n");
}

static void swap(unsigned *ids, unsigned src, unsigned dst) {
  unsigned tmp = ids[src];
  ids[src] = ids[dst];
  ids[dst] = tmp;
}

static void permutations(unsigned *ids, unsigned l, unsigned r) {
  if (l == r) {
    combination(ids);
    return;
  }

  for (unsigned i = l; i <= r; ++i) {
    swap(ids, l, i);
    permutation(ids, l + 1, r);
    swap(ids, l, i);
  }
}

permutations(ids, 0, nr_ids - 1);
