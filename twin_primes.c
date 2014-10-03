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
  int i = 2;
  int sqrt_n = sqrt(n);
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
    int start, end, len;
    scanf("%d %d %d\n", &start, &end, &len);
    if (start == 0 && end == 0 && len == 0) {
      break;
    }
    int prevprev = 2;
    int prev = 2;
    int prime_len = 0;
    for (; start < end && prime_len < len; start++) {
      if (is_prime(start)) {
        if (prev + 2 == start && prevprev + 2 != prev) {
          printf("(%d,%d)\n", prev, start);
          prime_len++;
        }
        prevprev = prev;
        prev = start;
      }
    }
  }
  return 0;
}
