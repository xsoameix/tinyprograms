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

parent_t parent_method_new(int x);
int parent_method_x(parent_t * self);

object_class_t *
parent_method_super(parent_t * self) {
  return 0;
}

parent_class_t Parent = {
  .name = "Parent",
  .super = &parent_method_super,
  .new = &parent_method_new,
  .x = &parent_method_x
};

parent_t
parent_method_new(int x) {
  parent_t self = {0};
  self.x = x;
  return self;
}

int
parent_method_x(parent_t * self) {
  return self->x;
}