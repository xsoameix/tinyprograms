:class Foo {

  struct {
    int x;
  }
}

:class Foos < Ary {}

· *
:new(int len) { return super(&Foos, len); }

int
:size(void) { return sizeof(foo_t); }

int
main(void) {
  int len;
  while (scanf("%d", &len) == 1) {
    foos_t * foos = Foos.new(len);
    foos·free;
  }
  return 0;
}
