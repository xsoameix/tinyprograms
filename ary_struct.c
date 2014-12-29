#include <stdio.h>

typedef struct {
  int a[2];
} foo_t;

int
main(void) {
  foo_t fo = {1,2};
  foo_t * fop = &fo;
  int i = 0;
  if (i == 0) {
    foo_t ba = * fop;
    ba.a[0] += 1;
    printf("ba %d %d\n", ba.a[0], ba.a[1]);
  }
  if (i == 0) {
    foo_t ba = * fop;
    printf("ba %d %d\n", ba.a[0], ba.a[1]);
  }
  return 0;
}
