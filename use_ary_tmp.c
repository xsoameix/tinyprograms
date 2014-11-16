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
typedef struct period_class period_class_t;
typedef struct period period_t;

struct period_class {
  char * name;
  object_class_t * (* super)(period_t *);
};

  struct period {
    union {
      period_class_t * class;
      period_class_t * _;
    };
    int x;
    int y;
  };


object_class_t *
period_method_super(period_t * self) {
  return 0;
}

period_class_t Period = {
  .name = "Period",
  .super = &period_method_super,
};

typedef struct periods_class periods_class_t;
typedef struct periods periods_t;

struct periods_class {
  char * name;
  ary_class_t * (* super)(periods_t *);
  int (* size)(void);
  periods_t * (* new)(int len);
  void * (* get)(periods_t * self, int i);
  int (* len)(periods_t * self);
  void (* free)(periods_t * self);
};

  struct periods {
    union {
      periods_class_t * class;
      periods_class_t * _;
    };
    int len;
    void * objs;
  };

int periods_method_size(void);
periods_t * periods_method_new(int len);
void * periods_method_get(periods_t * self, int i);
int periods_method_len(periods_t * self);
void periods_method_free(periods_t * self);

ary_class_t *
periods_method_super(periods_t * self) {
  return &Ary;
}

periods_class_t Periods = {
  .name = "Periods",
  .super = &periods_method_super,
  .new = &periods_method_new,
  .size = &periods_method_size,
  .get = (void *) &ary_method_get,
  .len = (void *) &ary_method_len,
  .free = (void *) &ary_method_free
};

periods_t *
periods_method_new(int len) { return Periods.super(0)->new(&Ary, len); }

int
periods_method_size(void) { return sizeof(period_t); }

int
main(void) {
  int len;
  while (scanf("%d", &len) == 1) {
    periods_t * pids = Periods.new(len);
    int i = 0;
    for (; i < pids->_->len(pids); i++) {
      period_t * p = pids->_->get(pids, i);
      scanf("%d%d", &p->x, &p->y);
    }
    i = 0;
    for (; i < pids->_->len(pids); i++) {
      period_t * pid = pids->_->get(pids, i);
      printf("[%d %d]\n", pid->x, pid->y);
    }
    puts(pids->class->name);
    pids->_->free(pids);
  }
  return 0;
}