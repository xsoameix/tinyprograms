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
#include <stdlib.h>

typedef struct foo_class foo_class_t;
typedef struct foo foo_t;

typedef int func_t(int);
struct foo_class {
  char * name;
  object_class_t * (* super)(foo_t *);
  foo_t * (* new)(int num);
  int (* add)(foo_t * self, func_t * yield);
};

  struct foo {
    union {
      foo_class_t * class;
      foo_class_t * _;
    };
    int num;
  };

foo_t * foo_method_new(int num);
int foo_method_add(foo_t * self, func_t * yield);

object_class_t *
foo_method_super(foo_t * self) {
  return 0;
}

foo_class_t Foo = {
  .name = "Foo",
  .super = &foo_method_super,
  .new = &foo_method_new,
  .add = &foo_method_add
};

foo_t *
foo_method_new(int num) {
  foo_t * self = calloc(1, sizeof(foo_t));
  self->class = &Foo;
  self->num = num;
  return self;
}

int
foo_method_add(foo_t * self, func_t * yield) {
  return yield(self->num);
}

int
inc(int x) {
  return x + 1;
}

int
main(void) {
  foo_t * foo = Foo.new(1);
  printf("%d\n", foo->_->add(foo, inc));
  free(foo);
  return 0;
}