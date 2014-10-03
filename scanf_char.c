#include <stdio.h>

int
main(void) {
  char a[10] = "123456\089";
  printf("%s", a);
  printf("%s\n", &a[7]);
  scanf("%2s\n", &a[1]);
  printf("%s", a);
  printf("%s\n", &a[7]);
  return 0;
}
