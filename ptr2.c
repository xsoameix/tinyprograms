#include <stdlib.h>

int
main(void) {
  int ** ptr = calloc(1, sizeof(int *));
  free(ptr);
  return 0;
}
