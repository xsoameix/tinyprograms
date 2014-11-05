#include <stdio.h>

int *
return_pointer(int ** value) {
  return * value;
}

int
main(void) {
  int num = 3;
  int * ptr = &num;
  * return_pointer(&ptr) = 4;
  printf("%d\n", num);
  return 0;
}
