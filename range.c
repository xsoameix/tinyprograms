#include <stdio.h>

typedef struct { int f, t; } g_t; /* range */

int
cmp(const void * a, const void * b) { return ((g_t *) a)->f - ((g_t *) b)->f; }

int
main(void) {
  g_t g[] = {{37,46},{30,43},{27,43},{5,15},{20,35},{0,46}},
      o[sizeof(g)/sizeof(*g)], * c = g+1, * p = o-1;
  int i, j, l = sizeof(g)/sizeof(*g), ol = 0;
  qsort(g, l, sizeof(*g), cmp);
  for (*++p = *g; c < g+l; c++) c->f-1 <= p->t &&
    (c->t>p->t && (p->t = c->t), 1) || (*++p = *c, 1);
  for (i = 0; i < l||!puts(""); i++) printf("[%d %d]", g[i].f, g[i].t);
  for (i = 0; i < p-o+1||!puts(""); i++) printf("[%d %d]", o[i].f, o[i].t);
  for (i = 0; i < p-o+1; i++)
    for (j = 0; j <= o[i].t || !puts(""); j++) putchar(j < o[i].f ? ' ' : '#');
  return 0;
}
