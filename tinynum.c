#include <stdio.h>
#include <stdlib.h>

void
bignum_add(int * a, int * b, int len) {
  int i = 0;
  for (; i < len; i++) {
    a[i] += b[i];
  }
  i = 0;
  for (; i < len; i++) {
    int carry = a[i] / 10;
    a[i] %= 10;
    a[i + 1] += carry;
  }
}

int *
create_bignum(int bits_len) {
  int len = 2500;
  int * ary = calloc(len, sizeof(int));
  ary[0] = 1;
  int i = 0;
  for (; i < bits_len; i++) {
    bignum_add(ary, ary, len);
  }
  return ary;
}

void
print_ary(int * ary) {
  int len = 2500;
  int i = 0;
  int print_zeros = 0;
  for (; i < len; i++) {
    int reverse_i = len - i - 1;
    if (print_zeros == 0 &&
        ary[reverse_i] != 0) {
      print_zeros = 1;
    }
    if (print_zeros) {
      printf("%d", ary[reverse_i]);
    }
  }
  puts("");
}

int
main(void) {
  int m_len, n_len;
  while (scanf("%d %d", &m_len, &n_len) == 2) {
    int * m = create_bignum(m_len);
    int * n = create_bignum(n_len);
    bignum_add(m, n, 2500);
    print_ary(m);
    free(m);
    free(n);
  }
  return 0;
}
