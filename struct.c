#include <stdio.h>

typedef struct {
  int x;
  int y;
} foo_t;

int
main(void) {
  foo_t a[] = {1, 2};
  foo_t b[] = {{1, 2}};
  printf("%d %d\n", a->x, b->x);
  return 0;
}
