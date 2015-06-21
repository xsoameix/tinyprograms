#include <stdio.h>

typedef struct {
  int a, b;
} foo_t;

int
main(void) {
  foo_t a[5];
  int i = 0;
  a[i++] = (foo_t) {i-2, i-1};
  return 0;
}
