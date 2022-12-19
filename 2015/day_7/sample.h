static wire_t wires[] = {
  { ASSIGN,  "123", NULL, "x", 0, false},
  { ASSIGN,  "456", NULL, "y", 0, false},
  { AND, "x", "y", "d", 0, false },
  { OR, "x", "y", "e", 0, false },
  { LSHIFT, "x", "2", "f", 0, false },
  { RSHIFT, "y", "2", "g", 0, false },
  { NOT, "x", NULL, "h", 0, false },
  { NOT, "y", NULL, "i", 0, false },
};

#define NR_WIRE 8
