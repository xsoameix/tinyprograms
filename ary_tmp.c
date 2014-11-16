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
#include <string.h>

typedef struct (null)_class (null)_class_t;
typedef struct (null) (null)_t;

struct (null)_class {
  char * name;
  (null)_class_t * (* super)((null)_t *);
  int (* size)(void);
  void * (* new)(void * class, int len);
  void * (* get)((null)_t * self, int i);
  int (* len)((null)_t * self);
  void (* free)((null)_t * self);
};

  struct (null) {
    union {
      (null)_class_t * class;
      (null)_class_t * _;
    };
    int len;
    void * objs;
  };

int (null)_method_size(void);
void * (null)_method_new(void * class, int len);
void * (null)_method_get((null)_t * self, int i);
int (null)_method_len((null)_t * self);
void (null)_method_free((null)_t * self);

(null)_class_t *
(null)_method_super((null)_t * self) {
  return 0;
}

(null)_class_t Ary = {
  .name = "Ary",
  .super = &(null)_method_super,
  .size = &(null)_method_size,
  .new = &(null)_method_new,
  .get = &(null)_method_get,
  .len = &(null)_method_len,
  .free = &(null)_method_free
};

int
(null)_method_size(void) {
  return 0;
}

void *
(null)_method_new(void * class, int len) {
  (null)_class_t * klass = class;
  (null)_t * self = calloc(1, sizeof((null)_t) + len * klass->size());
  self->class = class;
  self->len = len;
  self->objs = (void *) self + sizeof((null)_t);
  return self;
}

void *
(null)_method_get((null)_t * self, int i) {
  return self->objs + self->class.size() * i;
}

int
(null)_method_len((null)_t * self) {
  return self->len;
}

void
(null)_method_free((null)_t * self) {
  free(self);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ary_class ary_class_t;
typedef struct ary ary_t;

struct ary_class {
  char * name;
  object_class_t * (* super)(ary_t *);
  int (* size)(void);
  void * (* new)(void * class, int len);
  void * (* get)(ary_t * self, int i);
  int (* len)(ary_t * self);
  void (* free)(ary_t * self);
};

  struct ary {
    union {
      ary_class_t * class;
      ary_class_t * _;
    };
    int len;
    void * objs;
  };

int ary_method_size(void);
void * ary_method_new(void * class, int len);
void * ary_method_get(ary_t * self, int i);
int ary_method_len(ary_t * self);
void ary_method_free(ary_t * self);

object_class_t *
ary_method_super(ary_t * self) {
  return 0;
}

ary_class_t Ary = {
  .name = "Ary",
  .super = &ary_method_super,
  .size = &ary_method_size,
  .new = &ary_method_new,
  .get = &ary_method_get,
  .len = &ary_method_len,
  .free = &ary_method_free
};

int
ary_method_size(void) {
  return 0;
}

void *
ary_method_new(void * class, int len) {
  ary_class_t * klass = class;
  ary_t * self = calloc(1, sizeof(ary_t) + len * klass->size());
  self->class = class;
  self->len = len;
  self->objs = (void *) self + sizeof(ary_t);
  return self;
}

void *
ary_method_get(ary_t * self, int i) {
  return self->objs + self->class.size() * i;
}

int
ary_method_len(ary_t * self) {
  return self->len;
}

void
ary_method_free(ary_t * self) {
  free(self);
}