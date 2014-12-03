#include <stdio.h>

typedef struct {
  char a;
  char b;
  char c;
} foo_t;

typedef struct {
  char ary[sizeof(foo_t)];
} clone_t;

int
main(void) {
  clone_t foo;
  foo.ary[0] = 0;
  foo.ary[1] = 1;
  foo.ary[2] = 2;
  printf("foo:   %zu\n", sizeof(foo_t));
  printf("clone: %zu\n", sizeof(clone_t));
  return 0;
}
