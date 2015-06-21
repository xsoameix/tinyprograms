#include <stdio.h>
#include <stdlib.h>

typedef struct object_class object_class_t;
typedef struct object object_t;

struct object_class {
  char * name;
  object_class_t * (* super)(object_t *);
};

  struct object {
    union {
      object_class_t * class;
      object_class_t * _;
    };};

typedef struct point_class point_class_t;
typedef struct point point_t;

struct point_class {
  char * name;
  object_class_t * (* super)(point_t *);
};

  struct point {
    union {
      point_class_t * class;
      point_class_t * _;
    };
    int x, y;
  };

#define Point(...) ((point_t) {&Point, ##__VA_ARGS__})

object_class_t *
point_method_super(point_t * self) {
  return 0;
}

point_class_t Point = {
  .name = "Point",
  .super = &point_method_super,
};

typedef struct stack_class stack_class_t;
typedef struct stack stack_t;

struct stack_class {
  char * name;
  object_class_t * (* super)(stack_t *);
  void (* push)(stack_t * self, point_t point);
  point_t (* pop)(stack_t * self);
};

  struct stack {
    union {
      stack_class_t * class;
      stack_class_t * _;
    };
    int len;
    point_t * points;
  };

void stack_method_push(stack_t * self, point_t point);
point_t stack_method_pop(stack_t * self);
#define Stack(...) ((stack_t) {&Stack, ##__VA_ARGS__})

object_class_t *
stack_method_super(stack_t * self) {
  return 0;
}

stack_class_t Stack = {
  .name = "Stack",
  .super = &stack_method_super,
  .push = &stack_method_push,
  .pop = &stack_method_pop
};

void
stack_method_push(stack_t * self, point_t point) {
  self->points[self->len++] = point;
}

point_t
stack_method_pop(stack_t * self) {
  return self->points[--self->len];
}

int
main(void) {
  stack_t stack = Stack(0, malloc(100 * sizeof(point_t)));
  point_t ary[] = {Point(1, 2), Point(3, 4), Point(5, 6)};
  int i;
  for (i = 0; i < 3; i++) stack._->push(&stack, ary[i]);
  point_t point = stack._->pop(&stack);
  printf("(%d %d) ", point.x, point.y);
  point = stack._->pop(&stack);
  printf("(%d %d) ", point.x, point.y);
  point = stack._->pop(&stack);
  printf("(%d %d) ", point.x, point.y);
  return 0;
}