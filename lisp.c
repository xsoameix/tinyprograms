// Common Lisp:
//
// (defun foo (n)
//   (lambda (i) (incf n i)))

#include <stdio.h>
#include <stdlib.h>

typedef struct lambda {
  int n;
  int (* call)(struct lambda *, int);
} lambda_t;

int
inc(lambda_t * lambda, int i) {
  return lambda->n += i;
}

lambda_t *
foo(int n) {
  lambda_t * lambda = malloc(sizeof(lambda_t));
  lambda->n = n;
  lambda->call = inc;
  return lambda;
}

int
main(void) {
  lambda_t * lambda = foo(0);
  printf("%d\n", lambda->call(lambda, 1));
  printf("%d\n", lambda->call(lambda, 1));
  free(lambda);
  return 0;
}
