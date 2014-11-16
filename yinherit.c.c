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

#include <stdio.h>

typedef struct parent_class parent_class_t;
typedef struct parent parent_t;

struct parent_class {
  char * name;
  object_class_t * (* super)(parent_t *);
  int (* x)(parent_t * self);
};

  struct parent {
    union {
      parent_class_t * class;
      parent_class_t * _;
    };
    int x;
  };

int parent_method_x(parent_t * self);

object_class_t *
parent_method_super(parent_t * self) {
  return 0;
}

parent_class_t Parent = {
  .name = "Parent",
  .super = &parent_method_super,
  .x = &parent_method_x
};

int
parent_method_x(parent_t * self) {
  return self->x;
}

typedef struct child_class child_class_t;
typedef struct child child_t;

struct child_class {
  char * name;
  parent_class_t * (* super)(child_t *);
  int (* x)(child_t * self);
  child_t (* new)(int x, int y);
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

int child_method_x(child_t * self);
child_t child_method_new(int x, int y);
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
  return (child_t) {&Child, x, y};
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