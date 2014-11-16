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

typedef struct require2_class require2_class_t;
typedef struct require2 require2_t;

typedef struct require1_class require1_class_t;
typedef struct require1 require1_t;

struct require2_class {
  char * name;
  object_class_t * (* super)(require2_t *);
};

  struct require2 {
    union {
      require2_class_t * class;
      require2_class_t * _;
    };
    int a;
  };

extern require2_class_t Require2;
struct require1_class {
  char * name;
  object_class_t * (* super)(require1_t *);
};

  struct require1 {
    union {
      require1_class_t * class;
      require1_class_t * _;
    };
    int a;
  };

extern require1_class_t Require1;

typedef struct require1_class require1_class_t;
typedef struct require1 require1_t;

struct require1_class {
  char * name;
  object_class_t * (* super)(require1_t *);
};

  struct require1 {
    union {
      require1_class_t * class;
      require1_class_t * _;
    };
    int a;
  };


object_class_t *
require1_method_super(require1_t * self) {
  return 0;
}

require1_class_t Require1 = {
  .name = "Require1",
  .super = &require1_method_super,
};

