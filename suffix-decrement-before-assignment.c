#include <stdio.h>

int
main(void) {
  char ary[] = "abcde", a;
  int i = 3;
  while (i-- && (a = ary[i])) {
    putchar(ary[i]);
  }
  return 0;
}
