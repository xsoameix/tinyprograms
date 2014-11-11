typedef struct string_class string_class_t;
typedef struct string string_t;

extern string_class_t String;

struct string_class {
  string_t *    (* new)   (char *);
  void   (* init)  (string_t * self, char *);
  void   (* delete)    (string_t * self);
  string_class_t *   (* klass)     (string_t * self);
  char * (* class_name)(string_t * self);
  int    (* is_a)      (string_t * self, string_class_t * class);
  char * (* string)(string_t * self);
  size_t (* len)   (string_t * self);
  size_t (* s2i)   (string_t * self);
};

  struct string {
    union {
      string_class_t * class;
      string_class_t * _;
    };
  
    char * string;
  };

void string_class_init(void);

typedef struct array_class array_class_t;
typedef struct array array_t;

extern array_class_t Array;

struct array_class {
  array_t *    (* new)       (void);
  void   (* init)      (array_t * self);
  void   (* delete)    (array_t * self);
  array_class_t *   (* klass)     (array_t * self);
  char * (* class_name)(array_t * self);
  int    (* is_a)      (array_t * self, array_class_t * class);
  size_t (* len)(array_t * self);
};

  struct array {
    union {
      array_class_t * class;
      array_class_t * _;
    };
  
    size_t len;
  };

void array_class_init(void);

typedef struct object_class object_class_t;
typedef struct object object_t;

extern object_class_t Object;

struct object_class {
  object_t *    (* new)       (void);
  void   (* init)      (object_t * self);
  void   (* delete)    (object_t * self);
  object_class_t *   (* klass)     (object_t * self);
  char * (* class_name)(object_t * self);
  int    (* is_a)      (object_t * self, object_class_t * class);
};

  struct object {
    union {
      object_class_t * class;
      object_class_t * _;
    };
  };

void object_class_init(void);


#include <stdio.h>


string_class_t String;

string_t *
string_method_new(char *) {
}

void
string_method_init(string_t * self, char * val) {
  super.foo();
  self->_.super->init(self, "abc");
  self->_.super->init(self);
  self->_.super->initialize(self, "abc");
  self->_.super->initialize(self);
  self->_.super->initialize(self);
  self->_->initialize(self, "abc");
  self->_->initialize(self);
  self->_->initialize(self);
  self->string = val;

  string_t * str = String.new("abc");
  str->_->concat(str, "def");
  str->_->concat(str);
  str->_->concat(str);

  string_t str = String.new("abc");
  str._->concat(str, "def");
  str._->concat(str);
  str._->concat(str);
}

char *
string_method_string(string_t * self) {
  return self->string;
}

size_t
string_method_len(string_t * self) {
  return strlen(self->string);
}

void
string_class_init(void) {
  object_class_init();
  o_init_class((Object *) &String, (Object *) &Object, "String",
    sizeof(string_class_t), sizeof(string_t));
  String.new = string_method_new;
  String.init = string_method_init;
  String.string = string_method_string;
  String.len = string_method_len;
}

array_class_t Array;

size_t
array_method_len(array_t * self) {
  return self->len;
}

void
array_class_init(void) {
  object_class_init();
  o_init_class((Object *) &Array, (Object *) &Object, "Array",
    sizeof(array_class_t), sizeof(array_t));
  Array.len = array_method_len;
}

