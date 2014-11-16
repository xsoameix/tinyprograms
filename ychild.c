#include <stdio.h>

:require "yparent.c"

:class Child < Parent {

  struct {
    int y;
  }
}

·
:new(int x, int y) {
  parent_t parent = super(x);
  · self = {0};
  * (parent_t *) &self = parent;
  self.class = &Child;
  self.y = y;
  return self;
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
