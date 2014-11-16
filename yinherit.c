#include <stdio.h>

:class Parent {

  struct {
    int x;
  }
}

int
:x(self) {
  return @x;
}

:class Child < Parent {

  struct {
    int y;
  }
}

·
:new(int x, int y) {
  return (·) {&Child, x, y};
}

int
:y(self) {
  return @y;
}

int
main(void) {
  child_t child = Child.new(1, 2);
  printf("%s(%d, %d)\n", child.class->name, childˎx, childˎy);
  return 0;
}
