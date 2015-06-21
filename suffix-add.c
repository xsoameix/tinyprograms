#include <stdio.h>

int
main(void) {
  int i = 0;
  while (i++, printf("%d\n", i)) {
    if (i == 3) break;
  }
  return 0;
}
