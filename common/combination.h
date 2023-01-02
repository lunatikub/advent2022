/*
** nCr = (n r) = n! / r! x (r - n)!
*/
typedef struct combination {
  unsigned n;
  unsigned r;
  unsigned *idx;
  unsigned *combi;
} combination_t;

static void combination(combination_t *c) {
  printf("> ");
  for (unsigned i = 0; i < c->r; ++i) {
    printf("%u ", c->combi[i]);
    // const input_t *input = inputs[c->combi[i]]
  }
  printf("\n");
}

static void combination_init(combination_t *c, int n, int r) {
  c->n = n;
  c->r = r;
  c->idx = malloc(c->n * sizeof(unsigned));
  c->combi = malloc(c->r * sizeof(unsigned));
  for (unsigned i = 0; i < c->n; ++i) {
    c->idx[i] = i;
  }
}

static void combination_free(combination_t *c) {
  free(c->idx);
  free(c->combi);
}

static void combinations(combination_t *c, unsigned start, unsigned end,
                         unsigned idx) {
  if (idx == c->r) {
    combination_dump(c);
    return;
  }
  for (unsigned i = start; i <= end && end - i + 1 > c->r - idx; ++i) {
    c->combi[idx] = c->idx[i];
    combination(c, i + 1, end, idx + 1);
  }
}

combination_t c;
combination_init(&c, NR_INPUT, 1);
combinations(&c, 0, NR_INPUT, 0);
combination_free(&c);
