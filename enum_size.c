#include <stdio.h>

typedef enum {
  A,
  B,
  C
} foo_t;

int
main(void) {
  printf("sizeof enum %zu\n", sizeof(foo_t));
  return 0;
}
