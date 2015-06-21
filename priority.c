#include <stdio.h>

typedef struct {
  int n;
} foo;

int
main(void) {
  int n = 1;
  foo f = {2};
  foo * p = &f;
  n = f.n = p ? 3 : 4;
  return 0;
}
