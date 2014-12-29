#include <stdio.h>

typedef long long num_t;

#define LEN 10
#define DLEN 2 * LEN - 1 // Double length

num_t len;
num_t mat[LEN][LEN]; // score matrix
num_t q[LEN][LEN]; // result matrix
num_t c[DLEN]; // queen column array, 0: no queen, 1: queen
               // 0 1 2 3 ...
               // 0 1 2 3 ...
               // 0 1 2 3 ...
               // 0 1 2 3 ...
num_t l[DLEN]; // 0 1 2 3 ...
               // 1 2 3 ...
               // 2 3 ...
               // 3 ...
               // ...
               // i + j
num_t r[DLEN]; // ... 3 2 1 0
               //   ... 3 2 1
               //     ... 3 2
               //       ... 3
               //         ...
               // i + n - j
num_t score;
num_t max;

void
scan_mat(void) {
  num_t i = 0;
  for (; i < len; i++) {
    num_t j = 0;
    for (; j < len; j++) {
      scanf("%lld", &mat[i][j]);
      q[i][j] = 0;
    }
    c[i] = 0;
    l[i] = 0;
    r[i] = 0;
  }
  score = 0;
  max = 0;
}

num_t count = 0;

void
print_mat(void) {
  count++;
  num_t i = 0;
  for (; i < len; i++) {
    num_t j = 0;
    for (; j < len; j++) {
      if (q[i][j]) {
        printf(" o");
      } else {
        printf(" ·");
      }
    }
    puts("");
  }
  puts("");
}

void
queen(num_t i) {
  num_t j = 0;
  for (; j < len; j++) {
    if (c[j] || l[i + j] || r[i + len - j]) continue;
    c[j] = l[i + j] = r[i + len - j] = 1;
    q[i][j] = 1;
    score += mat[i][j];
    if (i == len - 1) {
      //print_mat();
      if (score > max) {
        max = score;
      }
    } else {
      queen(i + 1);
    }
    c[j] = l[i + j] = r[i + len - j] = 0;
    q[i][j] = 0;
    score -= mat[i][j];
  }
}

int
main(void) {
  while (1) {
    scanf("%lld", &len);
    if (len == 0) break;
    scan_mat();
    queen(0);
    printf("%lld\n", max);
  }
  return 0;
}
