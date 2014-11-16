#include <stdio.h>

typedef struct object_class object_class_t;
typedef struct object object_t;

extern object_class_t Object;

struct object_class {
};

  struct object {
    char * hello_world;
  };

void object_class_init(void);


#include <stdio.h>

object_class_t Object;

void
:realloc(self, h_size_t capa) {
  self->bins = realloc(self->bins, capa * sizeof(h_entry *));
  memset(self->bins, 0, capa * sizeof(h_entry *));
  self->capa = capa;
}

void
object_class_init(void) {
  class_init(&Object, 0, "Object",
    sizeof(object_class_t), sizeof(object_t));
}

