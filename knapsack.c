#include <stdio.h>
#include <string.h>

int
max(int a, int b) {
  return a > b ? a : b;
}

int
__main(void) {
  int n = 10, w = 10, c[11][11], i, j,
      weight[10] = {1,2,3,4,5,6,7,8,9,10}, cost[10] = {1,2,3,4,5,6,7,8,9,10};
  memset(c, 0, sizeof(c));
  for (i = 0; i < n; putchar('\n'), i++)
    for (j = 0; j <= w; j++) {
      printf("[%d %d %d]", i, j, weight[i]);
      c[i+1][j] = j - weight[i] >= 0 ?
          max(c[i][j], c[i][j - weight[i]] + cost[i]) : c[i][j];
    }
  for (i = 0; i <= n; putchar('\n'), i++)
    for (j = 0; j <= w; j++) printf("%2d ", c[i][j]);
  return 0;
}

int
_main(void) {
  int n = 10, w = 10, c[11], i, j,
      weight[10] = {1,2,3,4,5,6,7,8,9,10}, cost[10] = {1,2,3,4,5,6,7,8,9,10};
  memset(c, 0, sizeof(c));
  for (i = 0; i < n; putchar('\n'), i++) {
    for (j = w; j - weight[i] >= 0; j--)
      c[j] = max(c[j], c[j - weight[i]] + cost[i]);
    for (j = 0; j <= w; j++) printf("%2d ", c[j]);
  }
  return 0;
}

int
main(void) {
  int n = 10, w = 10, c[11], p[10][11], i, j,
      weight[10] = {1,2,3,4,5,6,7,8,9,10}, cost[10] = {1,2,3,4,5,6,7,8,9,10};
  memset(c, 0, sizeof(c));
  memset(p, 0, sizeof(p));
  for (i = 0; i < n; putchar('\n'), i++) {
    for (j = w; j - weight[i] >= 0; j--)
      if (c[j - weight[i]] + cost[i] > c[j])
        c[j] = c[j - weight[i]] + cost[i], p[i][j] = 1;
    for (j = 0; j <= w; j++) printf("%2d ", c[j]);
  }
  putchar('\n');
  for (i = 0; i < n; putchar('\n'), i++)
    for (j = 0; j <= w; j++)
      printf("%2d ", p[i][j]);
  for (i = n - 1, j = w; i >= 0; i--)
    if (p[i][j]) printf("[%d %d]", i, j), j -= weight[i];
  putchar('\n');
  return 0;
}
