#include <stdio.h>
#include <stdlib.h>

const int primes[] = {
    2,  3,  5,  7, 11, 13, 17, 19, 23, 29,
   31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
   73, 79, 83, 89, 97,101,103,107,109,113,
  127,131,137,139,149,151,157,163,167,173,
  179,181,191,193,197,199,211,223,227,229,
  233,239,241,251,257,263,269,271,277,281,
  283,293,307,311,313,317,331,337,347,349
};

void
print_ary(int * ary, int len) {
  int i = 0;
  for (; i < len; i++) {
    printf("%d", ary[i]);
    if (i != len - 1) {
      printf(" ");
    }
  }
  puts("");
}

void
print_sols(int * sol, int i, int sum, int len, int expected_sum) {
  int prime_i = 0;
  int prime = primes[prime_i];
  while (sum + prime <= expected_sum && i < len) {
    sol[i] = prime;
    print_sols(sol, i + 1, sum + prime, len, expected_sum);
    prime_i++;
    prime = primes[prime_i];
  }
  if (sum == expected_sum && i == len) {
    print_ary(sol, len);
  }
}

void
create_sols(int len, int expected_sum) {
  int * sol = calloc(len, sizeof(int));
  int i = 0;
  int sum = 0;
  if (len * 2 <= expected_sum) {
    print_sols(sol, i, sum, len, expected_sum);
  }
  puts("");
}

int
main(void) {
  int len, sum;
  while (scanf("%d %d\n", &len, &sum) == 2) {
    create_sols(len, sum);
  }
  return 0;
}
