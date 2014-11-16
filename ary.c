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

void *
:first(self) {
  return @objs;
}

void *
:last(self) {
  return @objs + @class->size() * (@len - 1);
}

int
:len(self) {
  return @len;
}

void
:free(self) {
  free(self);
}
