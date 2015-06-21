#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void
dfs(int x, int len, int lev, int mlv) {
  if (lev == mlv) return;
  int i;
  for (i = 0; i < len; i++) {
    int j;
    for (j = 0; j < lev; j++) {
      printf(" ");
    }
    printf("[%d] %d %d\n", lev + 1, len - i, x + i + 1);
    sleep(1);
    fflush(stdout);
    dfs(x + i + 1, len - i, lev + 1, mlv);
  }
}

int
_____main(void) {
  dfs(0, 4, 0, 4);
  return 0;
}

#define SIZE sizeof(int16_t)

int
____main(void) {
  /*static*/ char sf[SIZE * 3 * 4];
  * (int16_t *) &sf[SIZE * 0] = 0;
  * (int16_t *) &sf[SIZE * 1] = 4;
  * (int16_t *) &sf[SIZE * 2] = 0;
  int len = 1, mlv = 4;
  while (len--) {
    int x  = * (int16_t *) &sf[SIZE * 3 * len + SIZE * 0];
    int l  = * (int16_t *) &sf[SIZE * 3 * len + SIZE * 1];
    int lv = * (int16_t *) &sf[SIZE * 3 * len + SIZE * 2];
    int j;
    for (j = 0; j < lv; j++) {
      printf(" ");
    }
    printf("[%d] %d %d\n", lv, l, x);
    if (lv == mlv) continue;
    int i;
    for (i = 0; i < l; i++, len++) {
      * (int16_t *) &sf[SIZE * 3 * len + SIZE * 0] = x + l - i;
      * (int16_t *) &sf[SIZE * 3 * len + SIZE * 1] = i + 1;
      * (int16_t *) &sf[SIZE * 3 * len + SIZE * 2] = lv + 1;
    }
  }
  return 0;
}

typedef struct { int x, len, lv, sum; } nd;

int
___main(void) {
  /*static*/ nd t[1024 * 1024];
  /*static*/ int n[1024 * 2 - 1], a[1025];
  while (1) {
    int len = 1, mlv, i, j, _, yes = 1;
    _=scanf("%d", &mlv);
    if (!mlv) break;
    for (i = 0; i < 2 * mlv - 1; i++) _=scanf("%d", &i[n]);
    t[0] = (nd) {0, mlv, 0, 0};
    while (len--) {
      int x = t[len].x, l = t[len].len, lv = t[len].lv, s = t[len].sum;
      /*for (j = 0; j < lv; j++) printf(" ");
      printf("[%d] %d %d %d -[%d]\n", lv, l, x, s, n[x - 1]);*/
      a[lv] = n[x - 1];
      if (lv == mlv && !(s % mlv)) { yes = 0; break; }
      if (lv == mlv) continue;
      for (i = 0; i < l; i++, len++)
        t[len] = (nd) {x + l - i, i + 1, lv + 1, s + n[x + l - i - 1]};
    }
    printf("%s\n", yes ? "No" : "Yes");
    if (!yes) for (i = 0; i < mlv; i++)
      printf("%d%c", a[i + 1], i < mlv - 1 ? ' ' : '\n');
  }
  return 0;
}

/* d: Dynamic Programming
 * d[i,j,k] = d[i-1,j,k] || d[i-1,j,k]
 * i: n1, ... , n_i
 * j: n1, ... , n_j, j <= i, number of selected numbers
 * k: (n1 + ... + n_j) % n == k
 * d[i,j,k]: (n1 + ... + n_j) % n == k */

int
__main(void) {
  int l, n[1024 * 2 - 1], d[10 * 2][10 * 2][10], i, j, k, _;
  while (scanf("%d", &l) == 1 && l) {
    for (i = 0; i < 2 * l - 1; i++) _=scanf("%d", &i[n]);
    memset(d, 0, sizeof(d));
    for (i = 0; i <= 2 * l - 1; i++) d[i][0][0] = 1;
    for (i = 0; i < 2 * l - 1; i++)
      for (j = i + 1; j > 0; j--)
        for (k = 0; k < l; k++)
          d[i+1][j][k] = d[i][j][k] || d[i][j-1][((k-n[i])%l+l)%l];
    for (i = 0; i <= 2 * l - 1; i++) {
      printf("i = %d\n", i);
      for (j = 0; j <= 2 * l - 1; j++) {
        printf("  ");
        for (k = 0; k < l; k++)
          printf("%d ", d[i][j][k]);
        putchar('\n');
      }
    }
  }
  return 0;
}

#define S(a, i, j, k) (a[i][j][k/8] |= 1 << k%8) /* set bit */
#define G(a, i, j, k) (a[i][j][k/8] >> k%8 & 1) /* get bit */

int
_main(void) {
  /* p: print matrix */
  /*static*/ char d[1024 * 2][1024], p[1024 * 2 - 1][1024 * 2][1024/8];
  /*static*/ int l, n[1024 * 2 - 1], i, j, k, _;
  while (scanf("%d", &l) == 1 && l) {
    for (i = 0; i < 2 * l - 1; i++) _=scanf("%d", &i[n]);
    memset(d, 0, sizeof(d)), memset(p, 0, sizeof(p)), d[0][0] = 1;
    for (i = 0; i < 2 * l - 1; i++) {
      for (j = i + 1 < l ? i + 1 : l; j > 0; j--)
        for (k = 0; k < l; k++)
          if (!d[j][k] && d[j-1][((k-n[i])%l+l)%l])
            d[j][k] = 1, S(p, i, j, k);
      /*
      printf("i = %d\n", i);
      for (j = 0; j <= 2 * l - 1; j++) {
        printf("  ");
        for (k = 0; k < l; k++) {
          printf("%d ", d[j][k]);
        }
        putchar('\n');
      }
      */
    }
    /*
    for (i = 0; i < 2 * l - 1; i++) {
      printf("pi = %d\n", i);
      for (j = 0; j <= 2 * l - 1; putchar('\n'), j++) {
        printf("  ");
        for (k = 0; k < l; k++) printf("%d ", G(p, i, j, k));
      }
    }
    */
    for (i = 2 * l - 2, j = l; i >= 0; i--)
      if (G(p, i, j, 0)) break; /* set i, j to last (n0 +...+ nj)%l == 0 */
    puts("Yes");
    for (k = 0; i >= 0; i--)
      if (G(p, i, j, k))
        printf("%d%s", n[i], --j ? " " : ""), k = ((k-n[i])%l+l)%l;
    putchar('\n');
  }
  return 0;
}

typedef struct { int i, j, k; } s_t; /* stack frame, r: repeat */

static int16_t m[1500][1024+1][1024] = {0}, (*d)[1024];

int
main(void) {
  /* p: pointer for DP matrix, s: stack for top-down DP, t: top */
  static s_t s[2*(2*1024-1-1)+1], t;
  static int l, n[2*1024-1], si, mi = 0, i,j,k,v;
  while (~scanf("%d", &l), l) {
    for (i = 0; i < 2 * l - 1; i++) ~scanf("%d", &i[n]);
    v = 0, d = m[mi++], d[0][0] = -1, s[0] = (s_t) {2*l-2,l,0}, si = 1;
    while (si-- && (t = s[si], i = t.i, j = t.j, k = t.k, 1)) {
      if (j == 0 || j == i + 2 || d[j-1][((k-n[i])%l+l)%l] == i + 1 ||
          d[j][k] == i && d[j-1][((k-n[i])%l+l)%l] == i)
        d[j][k] = i + 1;
      else if (d[j-1][((k-n[i])%l+l)%l] < 0)
        d[j][k] = - i - 1, v = 1;
      else if (d[j][k] >= 0 && !v) si++,
        s[si++] = (s_t) {i-1,j-1,((k-n[i])%l+l)%l},
        s[si++] = (s_t) {i-1,j,k};
      /*
      printf("i = %d %d %d\n", i, j, k);
      for (j = 0; j <= l; j++) {
        printf("  ");
        for (k = 0; k < l; k++) {
          printf("%2d ", d[j][k]);
        }
        putchar('\n');
      }
      printf("          ");
      for (k = 0; k < si; k++) {
        printf("[%d %d %d]", s[k].i+1, s[k].j, s[k].k);
      }
      if (!s[si-1].r) printf(" <");
      putchar('\n');
      */
    }
    for (puts("Yes"), j = l, k = 0; j;)
      if (i = -d[j][k])
        printf("%d%s", n[i-1], --j ? " " : ""), k = ((k-n[i-1])%l+l)%l;
    putchar('\n');
  }
  return 0;
}
