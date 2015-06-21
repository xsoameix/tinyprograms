#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define S(a, i, j, k) (a[i][j][k/8] |= 1 << k%8) /* set bit */
#define G(a, i, j, k) (a[i][j][k/8] >> k%8 & 1) /* get bit */

int
main(void) {
  static char d[1024 * 2][1024], p[1024 * 2 - 1][1024 * 2][1024/8];
  static int l, n[1024 * 2 - 1], i, j, k, stop, _;
  while (scanf("%d", &l) == 1 && l) {
    for (i = 0; i < 2 * l - 1; i++) _=scanf("%d", &i[n]);
    memset(d, 0, sizeof(d)), memset(p, 0, sizeof(p)), d[0][0] = stop = 1;
    for (i = 0; stop && i < 2 * l - 1; i++) {
      for (j = i + 1 < l ? i + 1 : l; stop && j > 0; j--)
        for (k = 0; stop && k < l; k++)
          if (!d[j][k] && d[j-1][((k-n[i])%l+l)%l])
            d[j][k] = 1, S(p, i, j, k), stop = !(j == l && k == 0);
    }
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
