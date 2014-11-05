#include <stdint.h>

typedef struct {
  uint64_t a;
  uint64_t b;
  uint64_t c;
  uint64_t d;
  uint64_t e;
  uint64_t f;
} foo_t;

foo_t
return_foo(void) {
  return (foo_t) {1, 2};
}

void
call_foo(void) {
  foo_t foo = return_foo();
}
