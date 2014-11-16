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
typedef struct pman_class pman_class_t;
typedef struct pman pman_t;

struct pman_class {
  char * name;
  object_class_t * (* super)(pman_t *);
};

  struct pman {
    union {
      pman_class_t * class;
      pman_class_t * _;
    };
    int hit;
  };


object_class_t *
pman_method_super(pman_t * self) {
  return 0;
}

pman_class_t Pman = {
  .name = "Pman",
  .super = &pman_method_super,
};

typedef struct proad_class proad_class_t;
typedef struct proad proad_t;

struct proad_class {
  char * name;
  object_class_t * (* super)(proad_t *);
};

  struct proad {
    union {
      proad_class_t * class;
      proad_class_t * _;
    };
    int conn; // connected
  };


object_class_t *
proad_method_super(proad_t * self) {
  return 0;
}

proad_class_t Proad = {
  .name = "Proad",
  .super = &proad_method_super,
};

typedef struct pmans_class pmans_class_t;
typedef struct pmans pmans_t;

struct pmans_class {
  char * name;
  ary_class_t * (* super)(pmans_t *);
  int (* size)(void);
  pmans_t * (* new)(int len);
  void * (* get)(pmans_t * self, int i);
  int (* len)(pmans_t * self);
  void (* free)(pmans_t * self);
};

  struct pmans {
    union {
      pmans_class_t * class;
      pmans_class_t * _;
    };
    int len;
    void * objs;
  };

int pmans_method_size(void);
pmans_t * pmans_method_new(int len);
void * pmans_method_get(pmans_t * self, int i);
int pmans_method_len(pmans_t * self);
void pmans_method_free(pmans_t * self);

ary_class_t *
pmans_method_super(pmans_t * self) {
  return &Ary;
}

pmans_class_t Pmans = {
  .name = "Pmans",
  .super = &pmans_method_super,
  .new = &pmans_method_new,
  .size = &pmans_method_size,
  .get = (void *) &ary_method_get,
  .len = (void *) &ary_method_len,
  .free = (void *) &ary_method_free
};

pmans_t *
pmans_method_new(int len) { return Pmans.super(0)->new(&Pmans, len); }

int
pmans_method_size(void) { return sizeof(proad_t); }

typedef struct pmat_class pmat_class_t;
typedef struct pmat pmat_t;

struct pmat_class {
  char * name;
  matrix_class_t * (* super)(pmat_t *);
  int (* size)(void);
  pmat_t * (* new)(int len);
  void * (* get)(pmat_t * self, int row, int col);
  int (* len)(pmat_t * self);
  void (* free)(pmat_t * self);
  int (* conn)(pmat_t * self, int from, int to);
};

  struct pmat {
    union {
      pmat_class_t * class;
      pmat_class_t * _;
    };
    int len;
    void * objs;
  
    pmans_t * pmans;
  };

int pmat_method_size(void);
pmat_t * pmat_method_new(int len);
void * pmat_method_get(pmat_t * self, int row, int col);
int pmat_method_len(pmat_t * self);
void pmat_method_free(pmat_t * self);
int pmat_method_conn(pmat_t * self, int from, int to);

matrix_class_t *
pmat_method_super(pmat_t * self) {
  return &Matrix;
}

pmat_class_t Pmat = {
  .name = "Pmat",
  .super = &pmat_method_super,
  .new = &pmat_method_new,
  .size = &pmat_method_size,
  .conn = &pmat_method_conn,
  .get = (void *) &matrix_method_get,
  .len = (void *) &matrix_method_len,
  .free = (void *) &matrix_method_free
};

pmat_t *
pmat_method_new(int len) {
  pmat_t * pmat = Pmat.super(0)->new(&Pmat, len);
  pmat->pmans = Pmans.new(len);
  return pmat;
}

int
pmat_method_size(void) { return sizeof(pman_t); }

int
pmat_method_conn(pmat_t * self, int from, int to) {
  pmans_t * pmans = self->pmans;
  pman_t * pman = pmans->_->get(pmans, from);
  pman->hit = 1;
  int col = 0;
  for (; col < self->_->len(self); col++) {
    proad_t * road = self->_->get(self, from, col);
    pmans_t * pmans = self->pmans;
    pman_t * pman = pmans->_->get(pmans, col);
    if (road->conn && !pman->hit) {
      pman->hit = 1;
      if (col == to) return 1;
      int conn = self->_->conn(self, col, to);
      if (conn) return 1;
    }
  }
  return 0;
}

int
main(void) {
  int len, from, to;
  while (scanf("%d%d%d", &len, &from, &to) == 3) {
    pmat_t * pmat = Pmat.new(len);
    int row = 0;
    for (; row < pmat->_->len(pmat); row++) {
      int col = 0;
      for (; col < pmat->_->len(pmat); col++) {
        proad_t * proad = pmat->_->get(pmat, row, col);
        scanf("%d", &proad->conn);
      }
    }
    int conn = pmat->_->conn(pmat, from, to);
    printf("%s\n", conn ? "Y" : "N");
    pmat->_->free(pmat);
  }
  return 0;
}