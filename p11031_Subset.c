/* Looking for a subset */

#include <stdio.h>

long n[10000], t[10000], p[10000]; /* t: tmp */
int nl, q, ql, tl;

int
first_large(long * a, int l, int n) {
  int i = 0, m, h;
  while (l > 1) {
    h = l >> 1;
    m = a[i + h - 1];
    if (n <= m)  l = h;
    else i += h, l -= h;
  }
  return i;
}

int
first_small(long * a, int l, int n) {
  int i = 0, m, h;
  while (l > 1) {
    h = l >> 1;
    m = a[i + h - 1];
    if (n >= m)  l = h;
    else i += h, l -= h;
  }
  return i;
}

int
LIS(void) {
  if (!nl) return 0;
  tl = 0;
  t[tl++] = n[0];
  int i;
  for (i = tl; i < nl; i++) {
    int x = n[i];
    if (x > t[tl-1])
      t[tl++] = x;
    else
      t[first_large(t, tl, x)] = x;
  }
  for (i = 0; i < tl; i++) {
    printf("%ld ", t[i]);
  }
  putchar('\n');
  return tl;
}

long c[10000];

int
LIS_limit(int q) {
  if (!nl) return 0;
  tl = 0;
  t[tl++] = n[0];
  if (q == 1) {
    c[0] = t[0];
    return 1;
  }
  int i;
  for (i = tl; i < nl; i++) {
    int x = n[i];
    if (x > t[tl-1]) {
      t[tl++] = x;
      if (tl == q) {
        for (i = 0; i < tl; i++) {
          c[i] = t[i];
        }
        return tl;
      }
    } else {
      t[first_large(t, tl, x)] = x;
    }
  }
  return tl;
}

int
LDS(void) {
  if (!nl) return 0;
  tl = 0;
  t[tl++] = n[nl-1];
  c[0] = tl;
  int i;
  for (i = tl; i < nl; i++) {
    int x = n[nl-i-1], m;
    if (x < t[tl-1]) {
      t[tl++] = x;
      c[i] = tl;
    } else {
      m = first_small(t, tl, x);
      t[m] = x;
      c[i] = m + 1;
    }
  }
  /*int j;
  for (j = 0; j < nl; j++) {
    printf("%ld ", c[j]);
  }
  putchar('\n');
  putchar('\n');*/
  return tl;
}

int
main(void) {
  int _, set = 1;
  while (1) {
    _=scanf("%d%d", &nl, &ql);
    if (!nl && !ql) break;
    printf("Set %d:\n", set++);
    int i, j, l, p;
    for (i = 0; i < nl; i++) _=scanf("%ld", &n[i]);
    l = LDS();
    for (i = 0; i < ql; i++) {
      printf("  Subset %d:\n    ", i + 1);
      _=scanf("%d", &q);
      if (q <= l) {
        for (j = nl - 1, p = 100000000; j >= 0 && q; j--) {
          if (c[j] >= q && c[j] < p) {
            p = c[j];
            q--;
            printf("%ld%c", n[nl-j-1], q ? ' ' : '\n');
          }
        }
      } else {
        printf("Impossible\n");
      }
    }
  }
  return 0;
}
