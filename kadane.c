#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int num_t;

int
get_max(int a, int b) {
  return a > b ? a : b;
}

int
ary_max_sum_kadane(num_t * ary, num_t len,
                   num_t * max_begin, num_t * max_end) {
  num_t max_sum = ary[0];
  num_t sum = max_sum;
  num_t begin = 0;
  * max_begin, * max_end = 0;
  num_t i = 1;
  for (; i < len; i++) {
    if (sum < 0) {
      begin = i;
    }
    sum = get_max(sum + ary[i], ary[i]);
    if (sum > max_sum) {
      * max_begin = begin;
      * max_end = i;
    }
    max_sum = get_max(sum, max_sum);
  }
  return max_sum;
}

void
scan_ary(int * ary, int len) {
  int i = 0;
  for (; i < len; i++) {
    scanf("%d", &ary[i]);
  }
}

#define LEN 100000

int
main(void) {
  int len;
  while (1) {
    scanf("%d\n", &len);
    if (len == 0) break;
    static int ary[LEN];
    scan_ary(ary, len);
    num_t begin, end;
    int sum = ary_max_sum_kadane(ary, len, &begin, &end);
    printf("%d %d %d\n", sum, begin, end);
  }
  return 0;
}
