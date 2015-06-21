#include <stdio.h>

int
main(void) {
  int i = 0;
  printf("%d\n", 1 + i ? 2 : 3);
  printf("%d\n", i ? 2 : 3 + i);
  return 0;
}
