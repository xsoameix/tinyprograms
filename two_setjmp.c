#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

int
main(void) {
  jmp_buf foo = {0}, bar = {0};
  int fooj = setjmp(foo), barj = setjmp(bar);
  printf("foo jmp %d  bar jmp %d\n", fooj, barj);
  sleep(1);
  longjmp(bar, 1);
  return 0;
}
