#include <stdio.h>

int
main(void) {
  int ary[2] = {1,2};
  ary = {0};
  printf("%d %d\n", ary[0], ary[1]);
  return 0;
}
