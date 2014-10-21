#include <stdio.h>

#define ARY_ITOR(func) ((void (*)(void *, int)) func)

void
map(void (* itor)(void *, int)) {
  itor(NULL, 1);
}

int
main(void) {
  void itor(void) {
    puts("hello world");
  }
  map(ARY_ITOR(itor));
  return 0;
}
