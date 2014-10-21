#include <stdio.h>
#include <inttypes.h>

void
foo(void) {
  puts("hello ?");
}

typedef void (* func_t)(void);

void
call(uintptr_t func) {
  ((func_t) func)();
}

int
main(void) {
  call((uintptr_t) foo);
  return 0;
}
