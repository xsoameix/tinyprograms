#include <stdio.h>

void
foo(char d[10][10]) {
  printf("%zu\n", sizeof(char [10][10]));
  printf("%zu\n", sizeof(d));
}

int
main(void) {
  char d[10][10];
  foo(d);
  printf("%zu\n", sizeof(d));
  return 0;
}
