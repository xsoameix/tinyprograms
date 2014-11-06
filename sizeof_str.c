#include <stdio.h>

int
main(void) {
  char hello[] = "hello";
  printf("char[%zu]\n", sizeof(hello));
  return 0;
}
