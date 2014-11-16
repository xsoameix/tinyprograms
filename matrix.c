:class Matrix {

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
  · * self = calloc(1, sizeof(·) + len * len * klass->size());
  @class = class;
  @len = len;
  @objs = (void *) self + sizeof(·);
  return self;
}

void *
:get(self, int row, int col) {
  int size = @class->size();
  return @objs + @len * size * row + size * col;
}

int
:len(self) {
  return @len;
}

void
:free(self) {
  free(self);
}
