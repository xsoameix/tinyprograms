#include <stdio.h>

:require "object-c.c"

:class String {

  struct {
    char * string;
  }

  methods {
    · *    (* -new)   (char *);
    void   (* -init)  (self, char *);
    char * (* -string)(self);
    size_t (* -len)   (self);
    size_t (* -s2i)   (self);
  }
}

· *
:new(char *) {
}

void
:init(self, char * val) {
  super.foo();
  super("abc");
  super();
  super·initialize("abc");
  super·initialize();
  super·initialize;
  ·initialize("abc");
  ·initialize();
  ·initialize;
  @string = val;

  string_t * str = String.new("abc");
  str·concat("def");
  str·concat();
  str·concat;

  string_t str = String.new("abc");
  strˎconcat("def");
  strˎconcat();
  strˎconcat;
}

char *
:string(self) {
  return @string;
}

size_t
:len(self) {
  return strlen(@string);
}

:class Array < Object {

  struct {
    size_t len;
  }

  methods {
    size_t (* -len)(self);
  }
}

size_t
:len(self) {
  return @len;
}
