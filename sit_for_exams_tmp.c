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
  int (* len)(list_t * self);
  void * (* min)(list_t * self);
  int (* cmp)(list_t * self, void * a, void * b);
  void (* free)(list_t * self);
};

  struct list {
    union {
      list_class_t * class;
      list_class_t * _;
    };
    int len;
    lnode_t * head;
    lnode_t * tail;
  };

void * list_method_new(void * class);
void list_method_add(list_t * self, void * obj);
int list_method_remove(list_t * self, void * obj);
int list_method_len(list_t * self);
void * list_method_min(list_t * self);
int list_method_cmp(list_t * self, void * a, void * b);
void list_method_free(list_t * self);

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
  .min = &list_method_min,
  .cmp = &list_method_cmp,
  .free = &list_method_free
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
    if (node->fore) {
      node->fore->back = node->back;
    }
    if (node->back) {
      node->back->fore = node->fore;
    }
    if (node == self->head) {
      self->head = node->back;
    } else if (node == self->tail) {
      self->tail = node->fore;
    }
    free(node);
    self->len--;
    return 1;
  }
  return 0;
}

int
list_method_len(list_t * self) {
  return self->len;
}

void *
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

int
list_method_cmp(list_t * self, void * a, void * b) {
  return a - b;
}

void
list_method_free(list_t * self) {
  free(self);
}
#include <limits.h>

typedef struct town_class town_class_t;
typedef struct town town_t;

struct town_class {
  char * name;
  object_class_t * (* super)(town_t *);
};

  struct town {
    union {
      town_class_t * class;
      town_class_t * _;
    };
    int id;
    int limit;
    int cost;
  };


object_class_t *
town_method_super(town_t * self) {
  return 0;
}

town_class_t Town = {
  .name = "Town",
  .super = &town_method_super,
};

typedef struct towns_class towns_class_t;
typedef struct towns towns_t;

struct towns_class {
  char * name;
  ary_class_t * (* super)(towns_t *);
  int (* size)(void);
  towns_t * (* new)(int len);
  void * (* get)(towns_t * self, int i);
  void * (* first)(towns_t * self);
  void * (* last)(towns_t * self);
  int (* len)(towns_t * self);
  void (* free)(towns_t * self);
  void (* scan)(towns_t * self);
  void (* print)(towns_t * self);
};

  struct towns {
    union {
      towns_class_t * class;
      towns_class_t * _;
    };
    int len;
    void * objs;
  };

int towns_method_size(void);
towns_t * towns_method_new(int len);
void * towns_method_get(towns_t * self, int i);
void * towns_method_first(towns_t * self);
void * towns_method_last(towns_t * self);
int towns_method_len(towns_t * self);
void towns_method_free(towns_t * self);
void towns_method_scan(towns_t * self);
void towns_method_print(towns_t * self);

ary_class_t *
towns_method_super(towns_t * self) {
  return &Ary;
}

towns_class_t Towns = {
  .name = "Towns",
  .super = &towns_method_super,
  .new = &towns_method_new,
  .size = &towns_method_size,
  .scan = &towns_method_scan,
  .print = &towns_method_print,
  .get = (void *) &ary_method_get,
  .first = (void *) &ary_method_first,
  .last = (void *) &ary_method_last,
  .len = (void *) &ary_method_len,
  .free = (void *) &ary_method_free
};

towns_t *
towns_method_new(int len) { return Towns.super(0)->new(&Towns, len); }

int
towns_method_size(void) { return sizeof(town_t); }

void
towns_method_scan(towns_t * self) {
  int i = 0;
  for (; i < self->len; i++) {
    town_t * town = self->_->get(self, i);
    town->id = i;
    scanf("%d", &town->limit);
  }
}

void
towns_method_print(towns_t * self) {
  int i = 0;
  for (; i < self->len; i++) {
    town_t * town = self->_->get(self, i);
    printf("limit %d, cost %d\n", town->limit, town->cost);
  }
}

typedef struct tnode_class tnode_class_t;
typedef struct tnode tnode_t;

struct tnode_class {
  char * name;
  lnode_class_t * (* super)(tnode_t *);
  tnode_t * (* new)(town_t * town);
};

  struct tnode {
    union {
      tnode_class_t * class;
      tnode_class_t * _;
    };
    tnode_t * fore;
    tnode_t * back;
    void * obj;
  };

tnode_t * tnode_method_new(town_t * town);

lnode_class_t *
tnode_method_super(tnode_t * self) {
  return &Lnode;
}

tnode_class_t Tnode = {
  .name = "Tnode",
  .super = &tnode_method_super,
  .new = &tnode_method_new
};

tnode_t *
tnode_method_new(town_t * town) { return Tnode.super(0)->new(&Tnode, town); }

typedef struct tlist_class tlist_class_t;
typedef struct tlist tlist_t;

struct tlist_class {
  char * name;
  list_class_t * (* super)(tlist_t *);
  tlist_t * (* new)(void);
  void (* add)(tlist_t * self, void * obj);
  int (* remove)(tlist_t * self, void * obj);
  int (* len)(tlist_t * self);
  void * (* min)(tlist_t * self);
  int (* cmp)(tlist_t * self, void * a, void * b);
  void (* free)(tlist_t * self);
  void (* print)(tlist_t * self);
};

  struct tlist {
    union {
      tlist_class_t * class;
      tlist_class_t * _;
    };
    int len;
    lnode_t * head;
    lnode_t * tail;
  };

tlist_t * tlist_method_new(void);
void tlist_method_add(tlist_t * self, void * obj);
int tlist_method_remove(tlist_t * self, void * obj);
int tlist_method_len(tlist_t * self);
void * tlist_method_min(tlist_t * self);
int tlist_method_cmp(tlist_t * self, void * a, void * b);
void tlist_method_free(tlist_t * self);
void tlist_method_print(tlist_t * self);

list_class_t *
tlist_method_super(tlist_t * self) {
  return &List;
}

tlist_class_t Tlist = {
  .name = "Tlist",
  .super = &tlist_method_super,
  .new = &tlist_method_new,
  .cmp = &tlist_method_cmp,
  .print = &tlist_method_print,
  .add = (void *) &list_method_add,
  .remove = (void *) &list_method_remove,
  .len = (void *) &list_method_len,
  .min = (void *) &list_method_min,
  .free = (void *) &list_method_free
};

tlist_t *
tlist_method_new(void) { return Tlist.super(0)->new(&Tlist); }

int
tlist_method_cmp(tlist_t * self, void * a, void * b) {
  town_t * town_a = a;
  town_t * town_b = b;
  return town_a->cost - town_b->cost;
}

void
tlist_method_print(tlist_t * self) {
  tnode_t * node = (tnode_t *) self->head;
  printf("[");
  for (; node; node = node->back) {
    town_t * town = node->obj;
    printf("%d: ", town->id);
    if (town->cost == INT_MAX) {
      printf("max ");
    } else {
      printf("%d ", town->cost);
    }
  }
  printf("]\n");
}

typedef struct road_class road_class_t;
typedef struct road road_t;

struct road_class {
  char * name;
  object_class_t * (* super)(road_t *);
};

  struct road {
    union {
      road_class_t * class;
      road_class_t * _;
    };
    int cost;
  };


object_class_t *
road_method_super(road_t * self) {
  return 0;
}

road_class_t Road = {
  .name = "Road",
  .super = &road_method_super,
};

typedef struct tmat_class tmat_class_t;
typedef struct tmat tmat_t;

struct tmat_class {
  char * name;
  matrix_class_t * (* super)(tmat_t *);
  int (* size)(void);
  tmat_t * (* new)(towns_t * towns, int people);
  void * (* get)(tmat_t * self, int row, int col);
  int (* len)(tmat_t * self);
  void (* free)(tmat_t * self);
  void (* scan)(tmat_t * self);
  int (* cost)(tmat_t * self);
};

  struct tmat {
    union {
      tmat_class_t * class;
      tmat_class_t * _;
    };
    int len;
    void * objs;
  
    int people;
    towns_t * towns;
  };

int tmat_method_size(void);
tmat_t * tmat_method_new(towns_t * towns, int people);
void * tmat_method_get(tmat_t * self, int row, int col);
int tmat_method_len(tmat_t * self);
void tmat_method_free(tmat_t * self);
void tmat_method_scan(tmat_t * self);
int tmat_method_cost(tmat_t * self);

matrix_class_t *
tmat_method_super(tmat_t * self) {
  return &Matrix;
}

tmat_class_t Tmat = {
  .name = "Tmat",
  .super = &tmat_method_super,
  .new = &tmat_method_new,
  .size = &tmat_method_size,
  .scan = &tmat_method_scan,
  .cost = &tmat_method_cost,
  .get = (void *) &matrix_method_get,
  .len = (void *) &matrix_method_len,
  .free = (void *) &matrix_method_free
};

tmat_t *
tmat_method_new(towns_t * towns, int people) {
  int len = towns->_->len(towns);
  tmat_t * self = calloc(1, sizeof(tmat_t) + len * len * Tmat.size());
  self->class = &Tmat;
  self->len = len;
  self->objs = (void *) self + sizeof(tmat_t);
  self->towns = towns;
  self->people = people;
  return self;
}

int
tmat_method_size(void) { return sizeof(road_t); }

void
tmat_method_scan(tmat_t * self) {
  int row = 0;
  for (; row < self->len; row++) {
    int col = 0;
    for (; col < self->len; col++) {
      road_t * road = self->_->get(self, row, col);
      scanf("%d", &road->cost);
    }
  }
}

int
tmat_method_cost(tmat_t * self) {
  towns_t * towns = self->towns;
  town_t * town = towns->_->first(towns);
  town->cost = 0;
  int i = 1;
  for (; i < towns->_->len(towns); i++) {
    town_t * town = towns->_->get(towns, i);
    town->cost = INT_MAX;
  }
  tlist_t * list = Tlist.new();
  i = 0;
  for (; i < towns->_->len(towns); i++) {
    town_t * town = towns->_->get(towns, i);
    list->_->add(list, Tnode.new(town));
  }
  while (list->_->len(list)) {
    tnode_t * min = list->_->min(list);
    town_t * from = min->obj;
    //list·print;
    list->_->remove(list, min);
    int i = 0;
    for (; i < self->_->len(self); i++) {
      town_t * to = towns->_->get(towns, i);
      if (from->limit < self->people ||
          to->limit < self->people) continue;
      road_t * road = self->_->get(self, from->id, i);
      if (road->cost == -1) continue;
      int cost = from->cost + road->cost;
      //printf("from %d, to %d, cost %d + %d = %d\n",
      //       from->id, to->id,
      //       from->cost, road->cost, cost);
      if (cost < to->cost) {
        to->cost = cost;
      }
    }
  }
  list->_->free(list);
  town_t * last = towns->_->last(towns);
  return last->cost;
}

int
main(void) {
  int people, towns_len;
  while (scanf("%d%d", &people, &towns_len) == 2) {
    towns_t * towns = Towns.new(towns_len);
    tmat_t * tmat = Tmat.new(towns, people);
    towns->_->scan(towns);
    tmat->_->scan(tmat);
    int cost = tmat->_->cost(tmat);
    if (cost == INT_MAX) {
      printf("*\n");
    } else {
      printf("%d\n", cost);
    }
    //towns·print;
    tmat->_->free(tmat);
    towns->_->free(towns);
  }
  return 0;
}