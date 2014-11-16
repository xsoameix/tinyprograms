#include <stdio.h>

typedef struct foo foo_t;
typedef int func_t(foo_t * a);

struct foo {
  int (* a)(foo_t *);
  int (* b)(foo_t * a, func_t *);
  int c;
};

int func_a(foo_t * bar);
int func_b(foo_t * a, func_t * b);

foo_t bar = {
  .a = &func_a,
  .b = &func_b,
  .c = 1
};

int
func_a(foo_t * bar) {
  return bar->c;
}

int
func_b(foo_t * a, func_t * b) {
  return b(a);
}

int
main(void) {
  printf("%d\n", bar.b(&bar, func_a));
  return 0;
}
