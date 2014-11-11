typedef struct object_class object_class_t;
typedef struct object object_t;

extern object_class_t Object;

struct object_class {
  object_t *    (* new)       (void);
  void   (* init)      (object_t * self);
  void   (* delete)    (object_t * self);
  object_class_t *   (* klass)     (object_t * self);
  char * (* class_name)(object_t * self);
  int    (* is_a)      (object_t * self, object_class_t * class);
};

  struct object {
    union {
      object_class_t * class;
      object_class_t * _;
    };
  };

void object_class_init(void);


object_class_t Object;

static object_t *
object_method_new(void) {
  o_init_instance();
}

static void
object_method_initialize(object_t * self) {
}

static void
object_method_delete(object_t * self) {
  free(object_t * self);
}

static object_class_t *
object_method_klass(object_t * self) {
  return self->class;
}

static char *
:class_name(object_t * self) {
  return self->class->name;
}

static int
object_method_is_a(object_t * self, object_class_t * class) {
  object_class_t * klass = self->class;
  while (klass != NULL) {
    if (klass == class) return 1;
    klass = klass->super;
  }
  return 0;
}

void
object_class_init(void) {
  o_init_class(&Object, 0, "Object",
    sizeof(object_class_t), sizeof(object_t));
  Object.new = object_method_new;
  Object.initialize = object_method_initialize;
  Object.delete = object_method_delete;
  Object.klass = object_method_klass;
  Object.is_a = object_method_is_a;
}

