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
  return self->objs + self->class->size() * i;
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
typedef long long int num_t;

typedef struct cell_class cell_class_t;
typedef struct cell cell_t;

struct cell_class {
  char * name;
  object_class_t * (* super)(cell_t *);
};

  struct cell {
    union {
      cell_class_t * class;
      cell_class_t * _;
    };
    num_t count;
  };


object_class_t *
cell_method_super(cell_t * self) {
  return 0;
}

cell_class_t Cell = {
  .name = "Cell",
  .super = &cell_method_super,
};

typedef struct cells_class cells_class_t;
typedef struct cells cells_t;

struct cells_class {
  char * name;
  matrix_class_t * (* super)(cells_t *);
  int (* size)(void);
  cells_t * (* new)(int len, int left, int right);
  void * (* get)(cells_t * self, int row, int col);
  int (* len)(cells_t * self);
  void (* free)(cells_t * self);
  void (* move)(cells_t * self);
  void (* print)(cells_t * self);
};

  struct cells {
    union {
      cells_class_t * class;
      cells_class_t * _;
    };
    int len;
    void * objs;
  
    int left;
    int right;
  };

int cells_method_size(void);
cells_t * cells_method_new(int len, int left, int right);
void * cells_method_get(cells_t * self, int row, int col);
int cells_method_len(cells_t * self);
void cells_method_free(cells_t * self);
void cells_method_move(cells_t * self);
void cells_method_print(cells_t * self);

matrix_class_t *
cells_method_super(cells_t * self) {
  return &Matrix;
}

cells_class_t Cells = {
  .name = "Cells",
  .super = &cells_method_super,
  .new = &cells_method_new,
  .size = &cells_method_size,
  .move = &cells_method_move,
  .print = &cells_method_print,
  .get = (void *) &matrix_method_get,
  .len = (void *) &matrix_method_len,
  .free = (void *) &matrix_method_free
};

cells_t *
cells_method_new(int len, int left, int right) {
  cells_t * self = Cells.super(0)->new(&Cells, len);
  left = - left;
  right = - right;
  if (right < left) {
    int tmp = left;
    left = right;
    right = tmp;
  }
  self->left = left;
  self->right = right;
  return self;
}

int
cells_method_size(void) { return sizeof(cell_t); }

void
cells_method_move(cells_t * self) {
  int row = 0;
  for (; row < self->len - self->left; row++) {
    int col = self->left + row;
    for (; col <= self->right + row && col < self->len; col++) {
      cell_t * cell = self->_->get(self, row, col);
      if (row == 0) {
        cell->count = 1;
        continue;
      }
      cell_t * below = self->_->get(self, row - 1, col);
      cell_t * left = self->_->get(self, row, col - 1);
      if (col == self->left + row) {
        cell->count = below->count;
        continue;
      }
      if (col == self->right + row) {
        cell->count = left->count;
        continue;
      }
      cell->count = left->count + below->count;
    }
  }
}

void
cells_method_print(cells_t * self) {
  int row = 0;
  for (; row < self->len; row++) {
    int col = 0;
    for (; col < self->len; col++) {
      cell_t * cell = self->_->get(self, row, col);
      printf("%lld", cell->count);
      if (col != self->len - 1) {
        printf(" ");
      }
    }
    puts("");
  }
}

int
main(void) {
  int len, left, right;
  while (scanf("%d%d%d", &len, &left, &right) == 3) {
    cells_t * cells = Cells.new(len + 1, left, right);
    cells->_->move(cells);
    cell_t * cell = cells->_->get(cells, len, len);
    printf("%lld\n", cell->count);
    cells->_->free(cells);
  }
  return 0;
}