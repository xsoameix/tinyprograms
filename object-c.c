:class Object {

  struct {
    union {
      ·· * class;
      ·· * _;
    };
  }

  methods {
    · *    (* -new)       (void);
    void   (* -init)      (self);
    void   (* -delete)    (self);
    ·· *   (* -klass)     (self);
    char * (* -class_name)(self);
    int    (* -is_a)      (self, ·· * class);
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
