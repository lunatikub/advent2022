static int binstr_to_int(const char *str, unsigned len) {
  int n = 0;
  for (unsigned i = 0; i < len; ++i) {
    if (str[i] == '1')
      n |= 1 << (len - i - 1);
  }
  return n;
}
