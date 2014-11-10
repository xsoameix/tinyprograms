typedef struct object_class object_class_t;
typedef struct object object_t;

extern object_class_t Object;

struct object_class {
  object_t *    (* new)       (void);
  void   (* init)      (object_t * self);
  void   (* delete)    (object_t * self);
  object_class_t *   (* class)     (object_t * self);
  char * (* class_name)(object_t * self);
  bool   (* is_a)      (object_t * self, object_class_t * class);
};

  struct object {
    union {
      object_class_t * class;
      object_class_t * _;
    };
  };

void object_class_init(void);


object_class_t Object;

void
object_class_init(void) {
  o_init_class(&Object, 0, "Object",
    sizeof(object_class_t), sizeof(object_t));
}

