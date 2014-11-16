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

typedef struct foo_class foo_class_t;
typedef struct foo foo_t;

struct foo_class {
  char * name;
  object_class_t * (* super)(foo_t *);
  foo_t (* new)(int num);
  int (* num)(foo_t * self);
};

  struct foo {
    union {
      foo_class_t * class;
      foo_class_t * _;
    };
    int num;
  };

foo_t foo_method_new(int num);
int foo_method_num(foo_t * self);

object_class_t *
foo_method_super(foo_t * self) {
  return 0;
}

foo_class_t Foo = {
  .name = "Foo",
  .super = &foo_method_super,
  .new = &foo_method_new,
  .num = &foo_method_num
};

foo_t
foo_method_new(int num) {
  foo_t self = {0};
  self.class = &Foo;
  self.num = num;
  return self;
}

int
foo_method_num(foo_t * self) {
  return self->num;
}

int
main(void) {
  foo_t foo = Foo.new(1);
  printf("foo num: %d\n", foo._->num(&foo));
  return 0;
}