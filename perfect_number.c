#include <stdio.h>
#include <math.h>
#include <inttypes.h>

// input file:
//  tabe %:r-input
//
// Compile command:
//  :Compile

int
is_perfect(uint64_t n) {
  uint64_t i = 1;
  uint64_t sqrt_n = sqrt(n);
  uint64_t sum = 0;
  for (; i <= sqrt_n; i++) {
    if (n % i == 0) {
      sum += i;
      sum += n / i;
    }
  }
  if (fabs(sqrt(n) - (i - 1)) < 0.0001) {
    sum -= i;
  }
  return sum == 2 * n;
}

int
main(void) {
  uint64_t i = 8589869056;
  for (; i < 8589869156; i++) {
    if (is_perfect(i)) {
      printf("%" PRIu64 "\n", i);
    }
  }
  return 0;
}
