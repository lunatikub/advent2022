static inline bool is_number(const char *str) {
  for (unsigned i = 0; i < strlen(str); ++i) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}
