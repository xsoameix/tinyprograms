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

typedef struct ary_class ary_class_t;
typedef struct ary ary_t;

struct ary_class {
  char * name;
  object_class_t * (* super)(ary_t *);
  int (* size)(void);
  void * (* new)(void * class, int len);
  void * (* get)(ary_t * self, int i);
  void * (* first)(ary_t * self);
  void * (* last)(ary_t * self);
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
void * ary_method_first(ary_t * self);
void * ary_method_last(ary_t * self);
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
  .first = &ary_method_first,
  .last = &ary_method_last,
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
  return self->objs + self->class->size() * i;
}

void *
ary_method_first(ary_t * self) {
  return self->objs;
}

void *
ary_method_last(ary_t * self) {
  return self->objs + self->class->size() * (self->len - 1);
}

int
ary_method_len(ary_t * self) {
  return self->len;
}

void
ary_method_free(ary_t * self) {
  free(self);
}
typedef struct matrix_class matrix_class_t;
typedef struct matrix matrix_t;

struct matrix_class {
  char * name;
  object_class_t * (* super)(matrix_t *);
  int (* size)(void);
  void * (* new)(void * class, int len);
  void * (* get)(matrix_t * self, int row, int col);
  int (* len)(matrix_t * self);
  void (* free)(matrix_t * self);
};

  struct matrix {
    union {
      matrix_class_t * class;
      matrix_class_t * _;
    };
    int len;
    void * objs;
  };

int matrix_method_size(void);
void * matrix_method_new(void * class, int len);
void * matrix_method_get(matrix_t * self, int row, int col);
int matrix_method_len(matrix_t * self);
void matrix_method_free(matrix_t * self);

object_class_t *
matrix_method_super(matrix_t * self) {
  return 0;
}

matrix_class_t Matrix = {
  .name = "Matrix",
  .super = &matrix_method_super,
  .size = &matrix_method_size,
  .new = &matrix_method_new,
  .get = &matrix_method_get,
  .len = &matrix_method_len,
  .free = &matrix_method_free
};

int
matrix_method_size(void) {
  return 0;
}

void *
matrix_method_new(void * class, int len) {
  matrix_class_t * klass = class;
  matrix_t * self = calloc(1, sizeof(matrix_t) + len * len * klass->size());
  self->class = class;
  self->len = len;
  self->objs = (void *) self + sizeof(matrix_t);
  return self;
}

void *
matrix_method_get(matrix_t * self, int row, int col) {
  int size = self->class->size();
  return self->objs + self->len * size * row + size * col;
}

int
matrix_method_len(matrix_t * self) {
  return self->len;
}

void
matrix_method_free(matrix_t * self) {
  free(self);
}
typedef struct (null)_class (null)_class_t;
typedef struct (null) (null)_t;

struct (null)_class {
  char * name;
  (null)_class_t * (* super)((null)_t *);
  void * (* new)(void * class, void * obj);
};

  struct (null) {
    union {
      (null)_class_t * class;
      (null)_class_t * _;
    };
    (null)_t * fore;
    (null)_t * back;
    void * obj;
  };

void * (null)_method_new(void * class, void * obj);

(null)_class_t *
(null)_method_super((null)_t * self) {
  return 0;
}

(null)_class_t Lnode = {
  .name = "Lnode",
  .super = &(null)_method_super,
  .new = &(null)_method_new
};

void *
(null)_method_new(void * class, void * obj) {
  (null)_t * self = calloc(1, sizeof((null)_t));
  self->obj = obj;
  return self;
}

typedef struct (null)_class (null)_class_t;
typedef struct (null) (null)_t;

struct (null)_class {
  char * name;
  (null)_class_t * (* super)((null)_t *);
  void * (* new)(void * class);
  void (* add)((null)_t * self, void * obj);
  int (* remove)((null)_t * self, void * obj);
  void (* len)((null)_t * self);
  lnode_t * (* min)((null)_t * self);
};

  struct (null) {
    union {
      (null)_class_t * class;
      (null)_class_t * _;
    };
    int len;
    lnode * head;
    lnode * tail;
  };

void * (null)_method_new(void * class);
void (null)_method_add((null)_t * self, void * obj);
int (null)_method_remove((null)_t * self, void * obj);
void (null)_method_len((null)_t * self);
lnode_t * (null)_method_min((null)_t * self);

(null)_class_t *
(null)_method_super((null)_t * self) {
  return 0;
}

(null)_class_t List = {
  .name = "List",
  .super = &(null)_method_super,
  .new = &(null)_method_new,
  .add = &(null)_method_add,
  .remove = &(null)_method_remove,
  .len = &(null)_method_len,
  .min = &(null)_method_min
};

void *
(null)_method_new(void * class) {
  (null)_t * self = calloc(1, sizeof((null)_t));
  self->class = class;
  return self;
}

void
(null)_method_add((null)_t * self, void * obj) {
  lnode_t * new = obj;
  if (self->len) {
    self->tail->back = new;
    new->fore = self->tail;
    self->tail = new;
  } else {
    self->head = self->tail = new;
  }
  self->len++;
}

int
(null)_method_remove((null)_t * self, void * obj) {
  lnode_t * node = self->head;
  for (; node; node = node->back) {
    if (node != obj) continue;
    if (node == self->head) {
      self->head = node->back;
    } else if (node == self->tail) {
      self->tail = node->fore;
    } else {
      node->fore->back = node->back;
      node->back->fore = node->fore;
    }
    free(node);
    self->len--;
    return 1;
  }
  return 0;
}

void
(null)_method_len((null)_t * self) {
  return self->len;
}

lnode_t *
(null)_method_min((null)_t * self) {
  lnode_t * node = self->head;
  lnode_t * min = node;
  for (; node; node = node->back) {
    void * tmin = min->obj;
    void * town = node->obj;
    if (self->_->cmp(self, town, tmin) < 0) {
      min = node;
    }
  }
  return min;
}
typedef struct lnode_class lnode_class_t;
typedef struct lnode lnode_t;

struct lnode_class {
  char * name;
  object_class_t * (* super)(lnode_t *);
  void * (* new)(void * class, void * obj);
};

  struct lnode {
    union {
      lnode_class_t * class;
      lnode_class_t * _;
    };
    lnode_t * fore;
    lnode_t * back;
    void * obj;
  };

void * lnode_method_new(void * class, void * obj);

object_class_t *
lnode_method_super(lnode_t * self) {
  return 0;
}

lnode_class_t Lnode = {
  .name = "Lnode",
  .super = &lnode_method_super,
  .new = &lnode_method_new
};

void *
lnode_method_new(void * class, void * obj) {
  lnode_t * self = calloc(1, sizeof(lnode_t));
  self->obj = obj;
  return self;
}

typedef struct list_class list_class_t;
typedef struct list list_t;

struct list_class {
  char * name;
  object_class_t * (* super)(list_t *);
  void * (* new)(void * class);
  void (* add)(list_t * self, void * obj);
  int (* remove)(list_t * self, void * obj);
  void (* len)(list_t * self);
  lnode_t * (* min)(list_t * self);
};

  struct list {
    union {
      list_class_t * class;
      list_class_t * _;
    };
    int len;
    lnode * head;
    lnode * tail;
  };

void * list_method_new(void * class);
void list_method_add(list_t * self, void * obj);
int list_method_remove(list_t * self, void * obj);
void list_method_len(list_t * self);
lnode_t * list_method_min(list_t * self);

object_class_t *
list_method_super(list_t * self) {
  return 0;
}

list_class_t List = {
  .name = "List",
  .super = &list_method_super,
  .new = &list_method_new,
  .add = &list_method_add,
  .remove = &list_method_remove,
  .len = &list_method_len,
  .min = &list_method_min
};

void *
list_method_new(void * class) {
  list_t * self = calloc(1, sizeof(list_t));
  self->class = class;
  return self;
}

void
list_method_add(list_t * self, void * obj) {
  lnode_t * new = obj;
  if (self->len) {
    self->tail->back = new;
    new->fore = self->tail;
    self->tail = new;
  } else {
    self->head = self->tail = new;
  }
  self->len++;
}

int
list_method_remove(list_t * self, void * obj) {
  lnode_t * node = self->head;
  for (; node; node = node->back) {
    if (node != obj) continue;
    if (node == self->head) {
      self->head = node->back;
    } else if (node == self->tail) {
      self->tail = node->fore;
    } else {
      node->fore->back = node->back;
      node->back->fore = node->fore;
    }
    free(node);
    self->len--;
    return 1;
  }
  return 0;
}

void
list_method_len(list_t * self) {
  return self->len;
}

lnode_t *
list_method_min(list_t * self) {
  lnode_t * node = self->head;
  lnode_t * min = node;
  for (; node; node = node->back) {
    void * tmin = min->obj;
    void * town = node->obj;
    if (self->_->cmp(self, town, tmin) < 0) {
      min = node;
    }
  }
  return min;
}