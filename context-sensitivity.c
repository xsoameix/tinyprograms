typedef struct { int a; } foo_t;

int
main(void) {
  foo_t (x) = {1}; /* foo_t(x) is not a function */
  return 0;
}
