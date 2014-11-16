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

typedef struct parent_class parent_class_t;
typedef struct parent parent_t;

struct parent_class {
  char * name;
  object_class_t * (* super)(parent_t *);
  parent_t (* new)(int x);
  int (* x)(parent_t * self);
};

  struct parent {
    union {
      parent_class_t * class;
      parent_class_t * _;
    };
    int x;
  };

extern parent_class_t Parent;
parent_t parent_method_new(int x);
int parent_method_x(parent_t * self);
#include <stdio.h>


typedef struct child_class child_class_t;
typedef struct child child_t;

struct child_class {
  char * name;
  parent_class_t * (* super)(child_t *);
  child_t (* new)(int x, int y);
  int (* x)(child_t * self);
  int (* y)(child_t * self);
};

  struct child {
    union {
      child_class_t * class;
      child_class_t * _;
    };
    int x;
  
    int y;
  };

child_t child_method_new(int x, int y);
int child_method_x(child_t * self);
int child_method_y(child_t * self);

parent_class_t *
child_method_super(child_t * self) {
  return &Parent;
}

child_class_t Child = {
  .name = "Child",
  .super = &child_method_super,
  .new = &child_method_new,
  .y = &child_method_y,
  .x = (void *) &parent_method_x
};

child_t
child_method_new(int x, int y) {
  parent_t parent = Child.super(0)->new(x);
  child_t self = {0};
  * (parent_t *) &self = parent;
  self.class = &Child;
  self.y = y;
  return self;
}

int
child_method_y(child_t * self) {
  return self->y;
}

int
main(void) {
  child_t child = Child.new(1, 2);
  printf("%s(%d, %d)\n", child.class->name, child._->x(&child), child._->y(&child));
  return 0;
}