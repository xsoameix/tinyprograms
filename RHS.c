#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gvc.h> /* please add: `pkg-config libgvc --cflags --libs` */
/* AVL tree, k: key, d: data(trie root index), h: height */
typedef struct { int l, r, h, k, d; } a_t; /* TODO: Add LHS to data */
                          /* 1         3             */
int /* rotate left */     /*   3  => 1   4           */
arol(int * r, a_t * t) {  /*  2 4     2      c: copy */
  a_t * n = t+*r, * y = t+n->r, x = t[n->l], z = t[y->l]; int c = *r; *r = n->r,
  n->r = y->l, y->l = c, n->h = (x.h>z.h?x.h:z.h)+1, n->h<y->h||(y->h = n->h+1);
}
                          /*    4      2             */
int /* rotate right */    /*  2   => 1   4           */
aror(int * r, a_t * t) {  /* 1 3        3    c: copy */
  a_t * n = t+*r, * x = t+n->l, y = t[n->r], z = t[x->r]; int c = *r; *r = n->l,
  n->l = x->r, x->r = c, n->h = (y.h>z.h?y.h:z.h)+1, n->h<x->h||(x->h = n->h+1);
}

int /* insert, k: key, d: data, r: root, t: tree, s: stack, p: pointer     */
ains(int k, int d, int * r, a_t * t, int * tl) { /* o: orientation, c: cmp */
  a_t * n, x, y; int s[10] = {*r}, l = 1, * p, o, c, v = 0; /* v: valid    */
  while (l-- && (p = s+l, n = t+*p, o = k<n->k, 1) || (*r = *s, 0))
    if (!n->h) t[*p = (*tl)++] = (a_t) {0,0,1,k,d}, v = 1;
    else if (v) *(o ? &n->l : &n->r) = s[l+1], c = (x=t[n->l]).h-(y=t[n->r]).h,
      n->h = (c>0?x.h:y.h)+1, c < -1 && (k < y.k && aror(&n->r, t), arol(p, t)),
                              c > 1  && (k > x.k && arol(&n->l, t), aror(p, t));
    else l++, s[l++] = o ? n->l : n->r;
}

int /* fetch */
afet(int k, int * d, int r, a_t * t) {
  while (t[r].h > 1 && t[r].k - k) r = k < t[r].k ? t[r].l : t[r].r;
  return t[r].k == k && (* d = t[r].d, 1);
}

typedef struct { int d, c; } t_t; /* trie, d: data(AVL root index), c: count */

int /* insert, s: string, t: trie, a: AVL forest, n: AVL forest length */
tins(char * s, t_t * t, a_t * a, int * l, int * n) {
  int r = 0;
  while (*s && afet(*s, &r, t[r].d, a)) s++;
  while (*s || !++t[r].c) ains(*s++, *l, &t[r].d, a, n), r = (*l)++;
}

int /* next, true if children of trie root included it */
tnex(char s, int * r, t_t * t, a_t * a) {
  int c = * r;
  return (afet(s, &c, t[c].d, a) || !s && t[c].c) && (* r = c, 1);
}

typedef struct { int i, l; } r_t; /* range used by radix tree */

int /* TODO: insert */
rins(char * s, r_t * r, t_t * t, a_t * a, int * m, int * l, int * n) {
}

int
cmp(const void * a, const void * b) {
  char * x = * ((char **) a) + 2, * y = * ((char **) b) + 2;
  while (* x == * y && * x) x++, y++;
  return * x - * y;
}

int
main(void) {
  char * rhs[] = {"E:U","U:T","U:U+T","T:V","V:F","V:V*F","F:i","F:(E)"};
  int i, l = sizeof(rhs)/sizeof(*rhs);
  /*qsort(rhs, sizeof(char *), l, cmp);*/
  for (i = 0; i < l; i++) puts(rhs[i]);
  t_t t[100] = {0}; a_t a[100] = {0}; int r = 0, ar = 1, tl = 1, al = 1, d;
  /* test trie by assigning long sentances to trie *//*
  char * test[] = {"romane","romanus","romulus","rubens","ruber","rubicon",
    "rubicundus"};
  for (i = 0; i < sizeof test/sizeof *test; i++) tins(test[i], t, a, &tl, &al);
  */
  /* test trie by assigning character to trie node data */
  for (i = 0; i < l; i++) tins(rhs[i]+2, t, a, &tl, &al);
  printf("  has U(%d", r);printf("): %d\n", tnex('U', &r, t, a));
  printf("  has U(%d", r);printf("): %d\n", tnex('\0', &r, t, a));
  printf("  has U(%d", r);printf("): %d\n", tnex('\0', &r, t, a)), r = 0;
  printf("  has U+T(%d", r);printf("): %d\n", tnex('U', &r, t, a));
  printf("  has U+T(%d", r);printf("): %d\n", tnex('+', &r, t, a));
  printf("  has U+T(%d", r);printf("): %d\n", tnex('T', &r, t, a)), r = 0;
  printf("  has UF(%d", r);printf("): %d\n", tnex('U', &r, t, a));
  printf("  has UF(%d", r);printf("): %d\n", tnex('F', &r, t, a)), r = 0;
  printf("  has (E)(%d", r);printf("): %d\n", tnex('(', &r, t, a));
  printf("  has (E)(%d", r);printf("): %d\n", tnex('E', &r, t, a));
  printf("  has (E)(%d", r);printf("): %d\n", tnex(')', &r, t, a)), r = 0;
  printf("  has V*F(%d", r);printf("): %d\n", tnex('V', &r, t, a));
  printf("  has V*F(%d", r);printf("): %d\n", tnex('*', &r, t, a));
  printf("  has V*F(%d", r);printf("): %d\n", tnex('F', &r, t, a)), r = 0;
  printf("  has V*D(%d", r);printf("): %d\n", tnex('V', &r, t, a));
  printf("  has V*D(%d", r);printf("): %d\n", tnex('*', &r, t, a));
  printf("  has V*D(%d", r);printf("): %d\n", tnex('D', &r, t, a)), r = 0;
  /* test trie by assigning number to trie node data *//*
  char str[1] = {'\x00'};
  tins(str, t, a, &tl, &al);
  tins(str, t, a, &tl, &al);
  tins(str, t, a, &tl, &al);
  tins("\x09\x08", t, a, &tl, &al);
  tins("\x09\x08", t, a, &tl, &al);
  tins(str, t, a, &tl, &al);
  tins("\x09\x06", t, a, &tl, &al);
  tins("\x09\x07", t, a, &tl, &al);
  tins("\x08\x07", t, a, &tl, &al);
  printf("  has 0(%d", r);printf("): %d\n", tnex('\0', &r, t, a));
  printf("  has 8 7(%d", r);printf("): %d\n", tnex('\x08', &r, t, a));
  printf("  has 8 7(%d", r);printf("): %d\n", tnex('\x07', &r, t, a)), r = 0;
  printf("  has 9 9(%d", r);printf("): %d\n", tnex('\x09', &r, t, a));
  printf("  has 9 9(%d", r);printf("): %d\n", tnex('\x09', &r, t, a)), r = 0;
  printf("  has 9 7(%d", r);printf("): %d\n", tnex('\x09', &r, t, a));
  printf("  has 9 7(%d", r);printf("): %d\n", tnex('\x07', &r, t, a)), r = 0;
  printf("  has 9 8(%d", r);printf("): %d\n", tnex('\x09', &r, t, a));
  printf("  has 9 8(%d", r);printf("): %d\n", tnex('\x08', &r, t, a)), r = 0;
  printf("  has 9 6(%d", r);printf("): %d\n", tnex('\x09', &r, t, a));
  printf("  has 9 6(%d", r);printf("): %d\n", tnex('\x06', &r, t, a)), r = 0;
  */
  /* test AVL tree *//*
  ains(8, 9, &ar, a, &al);
  ains(3, 9, &ar, a, &al);
  ains(4, 9, &ar, a, &al);
  ains(5, 9, &ar, a, &al);
  ains(7, 9, &ar, a, &al);
  ains(6, 9, &ar, a, &al);
  printf("  fetch 0: %d\n", afet(0, &d, ar, a));
  printf("  fetch 1: %d\n", afet(1, &d, ar, a));
  printf("  fetch 2: %d\n", afet(2, &d, ar, a));
  printf("  fetch 3: %d\n", afet(3, &d, ar, a));
  printf("  fetch 4: %d\n", afet(4, &d, ar, a));
  printf("  fetch 5: %d\n", afet(5, &d, ar, a));
  printf("  fetch 6: %d\n", afet(6, &d, ar, a));
  printf("  fetch 7: %d\n", afet(7, &d, ar, a));
  printf("  fetch 8: %d\n", afet(8, &d, ar, a));
  printf("  fetch 9: %d\n", afet(9, &d, ar, a));
  */
  Agraph_t * g = agopen("g", Agdirected, 0);
  Agnode_t * tn[100], * an[100];
  Agedge_t * e;
  GVC_t * gvc = gvContext();
  char buf[250] = {0}; int bi = 0, m;
  agsafeset(g, "rankdir", "LR", "");
  for (i = 0; i < tl; i++)
    m = sprintf(buf+bi, "t%0X", i)+1,
    tn[i] = agnode(g, buf+bi, 1), bi += m,
    agsafeset(tn[i], "label", "Trie", ""),
    agsafeset(tn[i], "colorscheme", "ylgn9", ""),
    t[i].c && agsafeset(tn[i], "fillcolor", "4", ""),
    agsafeset(tn[i], "shape", "rectangle", ""),
    agsafeset(tn[i], "style", "rounded,filled", ""),
    agsafeset(tn[i], "fixedsize", "true", ""),
    agsafeset(tn[i], "fontname", "Sans", "");
  for (i = 0; i < al; i++)
    m = sprintf(buf+bi, "a%0X", i)+1,
    an[i] = agnode(g, buf+bi, 1), bi += m,
    m = sprintf(buf+bi, "%c", a[i].k ? a[i].k : '#')+1,
    agsafeset(an[i], "label", buf+bi, ""), bi += m,
    agsafeset(an[i], "shape", "circle", ""),
    agsafeset(an[i], "fontname", "Sans", ""),
    agsafeset(an[i], "colorscheme", "blues9", ""),
    agsafeset(an[i], "fillcolor", "4", ""),
    agsafeset(an[i], "style", "filled", "");
  for (i = 0; i < tl; i++)
    t[i].d && (e = agedge(g, tn[i], an[t[i].d], 0, 1),
               agsafeset(e, "arrowhead", "none", ""));
  for (i = 0; i < al; i++)
    a[i].l && (e = agedge(g, an[i], an[a[i].l], 0, 1),
               agsafeset(e, "colorscheme", "blues9", ""),
               agsafeset(e, "color", "7", "")),
    a[i].r && (e = agedge(g, an[i], an[a[i].r], 0, 1),
               agsafeset(e, "colorscheme", "blues9", ""),
               agsafeset(e, "color", "7", "")),
    e = agedge(g, an[i], tn[a[i].d], 0, 1),
    agsafeset(e, "arrowhead", "none", "");
  gvLayout(gvc, g, "dot");
  gvRenderFilename(gvc, g, "png", "graphviz.png");
  gvFreeLayout(gvc, g);
  agclose(g);
  return 0;
}
