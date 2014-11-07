#ifndef O_STRING_H
#define O_STRING_H

#include "object.h"

typedef struct string_class string_class_t;
typedef struct string string_t;

struct string_class {
  string_t *    (* new)   (char *);
  void   (* init)  (string_t * self, char *);
  void   (* delete)    (string_t * self);
  string_class_t *   (* class)     (string_t * self);
  char * (* class_name)(string_t * self);
  bool   (* is_a)      (string_t * self, string_class_t * class);
  char * (* string)(string_t * self);
  size_t (* len)   (string_t * self);
};

extern string_class_t String;

  struct string {
    union {
      string_class_t * class;
      string_class_t * _;
    };
  
    char * string;
  };

void string_class_init(void);

#endif
