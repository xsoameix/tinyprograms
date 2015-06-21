#include <stdio.h>
#include <stdlib.h>

:class Point {

  struct {
    int x, y;
  }
}

:class Stack {

  struct {
    int len;
    point_t * points;
  }
}

void
:push(self, point_t point) {
  @points[@len++] = point;
}

point_t
:pop(self) {
  return @points[--@len];
}

int
main(void) {
  stack_t stack = Stack(0, malloc(100 * sizeof(point_t)));
  point_t ary[] = {Point(1, 2), Point(3, 4), Point(5, 6)};
  int i;
  for (i = 0; i < 3; i++) stack∘push(ary[i]);
  point_t point = stack∘pop;
  printf("(%d %d) ", point.x, point.y);
  point = stack∘pop;
  printf("(%d %d) ", point.x, point.y);
  point = stack∘pop;
  printf("(%d %d) ", point.x, point.y);
  return 0;
}
