#include <stdio.h>
#include <stdlib.h>

:class Circle {

  struct {
    int radius;
  }
}

· *
:new(int radius) {
  · * self = calloc(1, sizeof(·));
  self->class = &Circle;
  self->radius = radius;
  return self;
}

int
:area(self) {
  return @radius * @radius;
}

int
main(void) {
  circle_t * circle = Circle.new(2);
  printf("circle area: %d\n", circle·area);
  free(circle);
  return 0;
}
