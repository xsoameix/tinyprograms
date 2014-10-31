#include <stdio.h>

typedef int lambda_t(int, int);

int
call(int a, int b) {
  return a + b;
}

int (* foo(int (* callback)(int, int)))(int, int) {
  return callback;
}

lambda_t *
bar(lambda_t * callback) {
  return callback;
}

int
main(void) {
  printf("%d\n", foo(call)(1, 2));
  printf("%d\n", bar(call)(1, 2));
  return 0;
}
