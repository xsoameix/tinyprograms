#include <stddef.h>
#include <string.h>

typedef struct object_class object_class_t;
typedef struct object object_t;

extern object_class_t Object;

struct object_class {
  object_class_t *   super;
  char * name;
  size_t size;
  size_t instance_size;
  object_t * (* new)(void);
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
  return 0;
}

void
class_init(object_class_t * class, object_class_t * super, char * class_name,
           size_t class_size, size_t instance_size) {
  if (class->size != 0) return;
  class->super = super;
  class->name = class_name;
  class->size = class_size;
  class->instance_size = instance_size;
  // inherit
  size_t offset = offsetof(object_class_t, new);
  if (class != &Object) {
    memcpy((char *) class + offset,
           (char *) class->super + offset,
           class->super->size - offset);
  }
}

void
object_class_init(void) {
  class_init(&Object, 0, "Object",
    sizeof(object_class_t), sizeof(object_t));
  Object.new = object_method_new;
}

