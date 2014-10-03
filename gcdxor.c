#include <stdio.h>
#include <stdlib.h>

// input file:
//  tabe %:r-input
//
// Compile command:
//  :Compile
// A B AXORB GCD(A,B)
// 0 0 0     0
// 0 1 1     1
// 1 0 1     0
// 1 1 0     1
// GCD(7, 6) == 1

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
  while (1) {
    int num;
    scanf("%d\n", &num);
    if (num == 0) {
      break;
    }
    int clone = num;
    int i = 1;
    while (clone > 1) {
      clone /= 2;
      i *= 2;
    }
    for (; i <= num; i++) {
      if (gcd(num, i) == (num ^ i)) {
        printf("(%d,%d)\n", num, i);
      }
    }
  }
  return 0;
}
