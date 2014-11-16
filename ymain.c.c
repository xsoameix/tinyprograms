typedef struct object_class {
  struct object_class * super;
  char * name;
} object_class_t;

#include <stdio.h>
#include <stdlib.h>

typedef struct circle_class circle_class_t;
typedef struct circle circle_t;

struct circle_class {
  object_class_t * super;
  char * name;
  circle_t * (* new)(int radius);
  int (* area)(circle_t * self);
};

  struct circle {
    union {
      circle_class_t * class;
      circle_class_t * _;
    };
    int radius;
  };

circle_t * circle_method_new(int radius);
int circle_method_area(circle_t * self);

circle_class_t Circle = {
  0,
  "Circle",
  &circle_method_new,
  &circle_method_area
};

circle_t *
circle_method_new(int radius) {
  circle_t * self = calloc(1, sizeof(circle_t));
  self->class = &Circle;
  self->radius = radius;
  return self;
}

int
circle_method_area(circle_t * self) {
  return self->radius * self->radius;
}

int
main(void) {
  circle_t * circle = Circle.new(2);
  printf("circle area: %d\n", circle->_->area(circle));
  free(circle);
  return 0;
}