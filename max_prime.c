#include <stdio.h>
#include <math.h>

// input file:
//  tabe %:r-input
//
// Compile command:
//  :Compile

int
is_prime(int n) {
  if (n < 2) {
    return 0;
  }
  int sqrt_n = sqrt(n);
  int i = 2;
  for (; i <= sqrt_n; i++) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}

int
main(void) {
  while (1) {
    int n;
    scanf("%d\n", &n);
    if (n == 0) {
      break;
    }
    int sqrt_n = sqrt(n);
    int i = n - 1;
    for (; i >= sqrt_n; i--) {
      if (is_prime(i)) {
        printf("%d %d\n", n, i);
        break;
      }
    }
  }
  return 0;
}
