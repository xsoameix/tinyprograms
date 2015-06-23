#include <stdio.h>

int
main(void) {
  int a = 10, b = 10; /* a: 1010, b: 1010 */
  a ^= b;
  b ^= a;
  a ^= b;
  printf("%d %d\n", a, b);
  return 0;
}
