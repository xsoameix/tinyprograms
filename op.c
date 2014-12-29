#include <stdio.h>
#include <string.h>

typedef long long num_t;

#define LEN 3000
num_t len;
num_t n[LEN];
num_t sum;
char ret[LEN];
num_t ri;
num_t can;

void
scan_ary(void) {
  num_t i = 0;
  for (; i < len; i++) {
    scanf("%lld", &n[i]);
  }
  memset(ret, 0, sizeof(ret));
}

void
print_ret(void) {
  num_t i = 0;
  for (; i < len; i++) {
    printf("%lld", n[i]);
    if (i != len - 1) {
      printf("%c", ret[i]);
    }
  }
  puts("");
}

void
produce(num_t i, num_t count) {
  if (count > sum || count > 30000) return;
  //print_ret();
  if (i == len) {
    if (count == sum) can = 1;
    return;
  }
  ri++;
  if (can) return;
  ret[ri - 1] = '+';
  produce(i + 1, count + n[i]);
  if (can) return;
  ret[ri - 1] = '*';
  produce(i + 1, count * n[i]);
  ri--;
}

int
main(void) {
  while (1) {
    scanf("%lld", &len);
    if (!len) break;
    scan_ary();
    scanf("%lld", &sum);
    can = 0;
    ri = 0;
    produce(1, n[0]);
    if (can) print_ret();
    else printf("Impossible\n");
  }
  return 0;
}
