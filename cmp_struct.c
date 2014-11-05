typedef struct {
  int a;
  int b;
  int c;
} foo_t;

int
main(void) {
  foo_t a = {1,2,3};
  if (a != 0) {
    a.a += 1;
  }
  return 0;
}
