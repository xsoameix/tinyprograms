#include <stdio.h>

int
main(void) {
  int * a[10], ** b = a, ** c = a;
  printf("%p\n%p\n%p\n", a, b, c);
  return 0;
}
