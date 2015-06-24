#include <stdio.h>

typedef struct { int a, b; } a_t;
typedef struct { a_t * a, * b; } b_t;

int
print(b_t * foo, int len) {
}

int
main(void) {
  b_t b = {(a_t[2]) {0}, (a_t[2]) {0}};
  return 0;
}
