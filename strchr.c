#include <stdio.h>
#include <string.h>

int
main(void) {
  printf("%p\n", strchr("abc", 'a'));
  printf("%p\n", strchr("abc", 'b'));
  printf("%p\n", strchr("abc", 'c'));
  printf("%p\n", strchr("abc", 0));
  printf("%d\n", strchr("abc", 'd') == 0);
  return 0;
}
