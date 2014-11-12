:class Object {

  struct {
    union {
      ·· * class;
      ·· * _;
    };
  }

  methods {
    ·· *   -super;
    char * -name;
    size_t -size;
    size_t -instance_size;
    · *    (* -new)       (void);
    void   (* -init)      (self);
    void   (* -delete)    (self);
  }
}

void
class_init(·· * class, ·· * super, char * class_name,
           size_t class_size, size_t instance_size) {
  if (class->size != 0) return;
  class->super = super;
  class->name = class_name;
  class->size = class_size;
  class->instance_size = instance_size;
  // inherit
  size_t offset = offsetof(··, new);
  if (class != &Object) {
    memcpy((char *) class + offset,
           (char *) class->super + offset,
           class->super->size - offset);
  }
}

:end
