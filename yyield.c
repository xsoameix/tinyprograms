#include <stdio.h>
#include <stdlib.h>

:class Foo {

  struct {
    int num;
  }
}

· *
:new(int num) {
  · * self = calloc(1, sizeof(·));
  self->class = &Foo;
  self->num = num;
  return self;
}

:typedef int func_t(int);

int
:add(self, func_t * yield) {
  return yield(@num);
}

int
inc(int x) {
  return x + 1;
}

int
main(void) {
  foo_t * foo = Foo.new(1);
  printf("%d\n", foo·add(inc));
  free(foo);
  return 0;
}
