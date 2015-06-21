#include <stdio.h>

int
lower_bound(long * a, int al, int n) {
  int l = al >> 1, i = l, x;
  while (al > 1) {
    x = a[i - 1];
    printf("al %d  l %d  i %d\n", al, l, i);
    if (n <= x) {
      i -= l - (l >> 1);
    } else {
      l = al - l, i += (l >> 1);
    }
    al = l, l >>= 1;
  }
  printf("%d\n", i);
  return i;
}

int
lower_bound2(long * a, int l, int n) {
  int i = 0, m, h;
  while (l > 1) {
    printf("i %d  l %d\n", i, l);
    h = l >> 1;
    m = a[i + h - 1];
    if (n <= m)  l = h;
    else i += h, l -= h;
  }
  printf("%d\n", i);
  return i;
}

int
main(void) {
  long a[] = {1,2,2,3,3,4};
  lower_bound2(a, sizeof(a) / sizeof(a[0]), 2);
  lower_bound2(a, sizeof(a) / sizeof(a[0]), 3);
  lower_bound2(a, sizeof(a) / sizeof(a[0]), 4);
  long b[] = {1,2,2,3,3,4,4};
  lower_bound2(b, sizeof(b) / sizeof(b[0]), 2);
  lower_bound2(b, sizeof(b) / sizeof(b[0]), 3);
  lower_bound2(b, sizeof(b) / sizeof(b[0]), 4);
  return 0;
}
