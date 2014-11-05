typedef struct {
  int a;
  int b;
  int c;
} foo_t;

int
main(void) {
  foo_t foo = {1,2,3};
  foo = (foo_t) {0};
  return 0;
}
