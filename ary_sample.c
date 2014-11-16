#include <stdio.h>
#include <stdlib.h>
#include <string.h>

:class Ary {

  struct {
    int len;
    void * objs;
  }
}

int
:size(void) {
  return 0;
}

void *
:new(void * class, int len) {
  ·· * klass = class;
  · * self = calloc(1, sizeof(·) + len * klass->size());
  @class = class;
  @len = len;
  @objs = (void *) self + sizeof(·);
  return self;
}

void *
:get(self, int i) {
  return @objs + @class->size() * i;
}

int
:len(self) {
  return @len;
}

void
:free(self) {
  free(self);
}

:inherited(class)

· *
:new(int len) { return super(&class, len); }

int
:size(void) { return sizeof(·); }

:macro

:each array { |obj, index|
  int index = 0;
  · * obj = array·get(index);
  for (; index < array·len; index++) {
    yield
  }
}
