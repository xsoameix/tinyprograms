typedef struct object_class object_class_t;
typedef struct object object_t;

extern object_class_t Object;

struct object_class {
  object_t *    (* new)       (void);
};

  struct object {
    char * a;
  };

void object_class_init(void);


object_class_t Object;

void
object_class_init(void) {
  class_init(&Object, 0, "Object",
    sizeof(object_class_t), sizeof(object_t));
}

