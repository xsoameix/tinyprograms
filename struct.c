#include <stdio.h>

typedef struct {
  int a;
  int b;
} foo_t;

int
main(void) {
  int a = 1;
  int b = 2;
  foo_t foo;
  foo = (foo_t) {.b = b, .a = a};
  printf("%d %d\n", foo.a, foo.b);
  return 0;
}
