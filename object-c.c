:class Object {

  struct {
    union {
      ·· * class;
      ·· * _;
    };
  }

  class {
    ·· *   -super;
    char * -name;
    size_t -size;
    size_t -instance_size;
  }
}

static · *
:new(void) {
  o_init_instance();
}

static void
:initialize(self) {
}

static void
:delete(self) {
  free(self);
}

static ·· *
:klass(self) {
  return @class;
}

static char *
:class_name(self) {
  return @class->name;
}

static int
:is_a(self, ·· * class) {
  ·· * klass = @class;
  while (klass != NULL) {
    if (klass == class) return 1;
    klass = klass->super;
  }
  return 0;
}
