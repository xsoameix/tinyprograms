#include <stdio.h>

void
func(int a) {
  printf("func: %d\n", a);
}

int
main(void) {
  int a = 1;
  func(a = 2);
  return 0;
}
