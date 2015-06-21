typedef struct {
  int a[3];
} ary;

int
main(void) {
  /*int a[3];
  int b[3] = {1, 2, 3};
  a = b;*/
  ary a;
  ary b = {1, 2, 3};
  a = b;
  return 0;
}
