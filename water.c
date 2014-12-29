#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef long long num_t;

#define LEN 3
#define EXPECTED_LEN 210

num_t cups[LEN];
num_t upper[LEN]; // upper bound
num_t expected, lim; // expected, limit
num_t rest[EXPECTED_LEN];
num_t cost[EXPECTED_LEN][EXPECTED_LEN][EXPECTED_LEN];

void
pcups(void) {
  num_t i = 0;
  for (; i < LEN; i++) {
    printf("%lld ", cups[i]);
  }
  puts("");
  //printf("total %lld\n", total);
}

num_t
min(num_t a, num_t b) {
  return a < b ? a : b;
}

num_t *
get_cost(void) {
  return &cost[cups[0]][cups[1]][cups[2]];
}

void
can(num_t total) {
  if (total >= * get_cost() ||
      total >= rest[expected]) return;
  //pcups();
  num_t i = 0;
  for (; i < LEN; i++) {
    rest[cups[i]] = min(rest[cups[i]], total);
  }
  num_t * thecost = get_cost();
  * thecost = total;

  num_t from = 0;
  for (; from < LEN; from++) {
    num_t step = 1;
    for (; step <= LEN - 1; step++) {
      num_t to = (from + step) % LEN;
      num_t transfer = min(cups[from], upper[to] - cups[to]);
      cups[from] -= transfer;
      cups[to] += transfer;
      can(total + transfer);
      cups[to] -= transfer;
      cups[from] += transfer;
    }
  }
}

int
main(void) {
  while (1) {
    scanf("%lld", &upper[0]);
    scanf("%lld", &upper[1]);
    scanf("%lld", &upper[2]);
    cups[0] = 0;
    cups[1] = 0;
    cups[2] = upper[2];
    scanf("%lld", &expected);
    scanf("%lld", &lim);
    num_t i = 0;
    for (; i <= upper[0]; i++) {
      num_t j = 0;
      for (; j <= upper[1]; j++) {
        num_t k = 0;
        for (; k <= upper[2]; k++) {
          cost[i][j][k] = INT_MAX;
        }
      }
    }
    i = 0;
    for (; i <= expected; i++) {
      rest[i] = INT_MAX;
    }
    if (upper[0] == 0 &&
        upper[1] == 0 &&
        upper[2] == 0 &&
        expected == 0 &&
        lim == 0) break;
    can(0);
    printf("%s\n",
           rest[expected] != INT_MAX &&
           rest[expected] <= lim ? "YES" : "NO");
  }
  return 0;
}
