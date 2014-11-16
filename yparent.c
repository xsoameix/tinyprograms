:class Parent {

  struct {
    int x;
  }
}

·
:new(int x) {
  · self = {0};
  self.x = x;
  return self;
}

int
:x(self) {
  return @x;
}
