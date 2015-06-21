#include <stdio.h>

int
main(void) {
  int i = 0, j;
  for (1 + 1; i < 3; for (j = 0; j < 3; j++) printf("j %d\n", j);)
    printf("i %d\n", i++);
  return 0;
}
