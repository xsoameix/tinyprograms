#include <stdio.h>

// input file:
//  tabe %:r-input
//
// Compile command:
//  :Compile

int
gcd(int a, int b) {
  int c;
  while (a != 0) {
    c = a;
    a = b % a;
    b = c;
  }
  return c;
}

int
main(void) {
  int len;
  scanf("%d\n", &len);
  int i = 0;
  for (; i < len; i++) {
    int a, b, c;
    scanf("%d,%d,%d\n", &a, &b, &c);
    printf("%d\n", gcd(gcd(a, b), c));
  }
  return 0;
}
