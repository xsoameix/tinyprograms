#include <stdio.h>

int
func(int i) {
  printf("check i: %d\n", i);
  return i < 3;
}

int
main(void) {
  int i = 0;
  while (i < 3 && func(i)) i++;
  return 0;
}
