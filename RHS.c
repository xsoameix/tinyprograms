#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gvc.h> /* please add: `pkg-config libgvc --cflags --libs` */
/* AVL tree, k: key, d: data(trie root index), h: height */
typedef struct { int l, r, h, k, d; } a_t;
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

typedef int acmp_t(int key, int compared, void * data);
    /*         k: key, d: data, r: root, t: tree, s: stack, p: pointer */
int /* insert, c: cmp, o: orientate, v: valid, m: cmp func */
ains(int k, int d, int * r, a_t * t, int * tl, acmp_t * m, void * u) {
  a_t * n, x, y; int s[10] = {*r}, l = 1, * p, o, c, v = 0;
  while (l-- && (p = s+l, n = t+*p, o = m(k,n->k,u)<0, 1) || (*r = *s, 0))
    if (!n->h) t[*p = (*tl)++] = (a_t) {0,0,1,k,d}, v = 1;
    else if (v) *(o ? &n->l : &n->r) = s[l+1], c = (x=t[n->l]).h-(y=t[n->r]).h,
      n->h = (c>0?x.h:y.h)+1, c < -1 && (m(k,y.k,u)<0&&aror(&n->r,t),arol(p,t)),
                              c > 1  && (m(k,x.k,u)>0&&arol(&n->l,t),aror(p,t));
    else l++, s[l++] = o ? n->l : n->r;
}

int /* fetch */
afet(int k, int * d, int r, a_t * t, acmp_t * m, void * u) {
  while (t[r].h > 1 && m(k,t[r].k,u)) r = m(k,t[r].k,u)<0 ? t[r].l : t[r].r;
  return t[r].h && !m(k,t[r].k,u) && (* d = r, 1);
}

typedef struct { int d, c; } t_t; /* trie, d: data(AVL root index), c: count */

int
tm(int a, int b, void * _) { return a - b; }

int /* insert, s: string, t: trie, a: AVL forest, n: AVL forest length */
tins(char * s, t_t * t, a_t * a, int * l, int * n) {
  int r = 0;
  while (*s && afet(*s, &r, t[r].d, a, tm, 0)) r = a[r].d, s++;
  while (*s || !++t[r].c) ains(*s++, *l, &t[r].d, a, n, tm, 0), r = (*l)++;
}

int /* map, map string to data (!= 0) */
tmap(char * s, int d, t_t * t, a_t * a, int * l, int * n) {
  int r = 0;
  while (*s && afet(*s, &r, t[r].d, a, tm, 0)) r = a[r].d, s++;
  while (*s || (t[r].c = d,0)) ains(*s++, *l, &t[r].d, a, n, tm, 0), r = (*l)++;
}

int /* next, true if children of trie root included it */
tnex(char s, int * r, t_t * t, a_t * a) {
  int c = * r; /* c: copy */
  return afet(s, &c, t[c].d, a, tm, 0) && (* r = a[c].d, 1) || !s && t[c].c;
}

int /* retrieve, 0 if the data does not exist or no children of included it */
tret(char s, int * r, t_t * t, a_t * a) {
  int c = * r;
  return afet(s, &c, t[c].d, a, tm, 0) ? (*r = a[c].d, t[*r].c) : s ? 0:t[c].c;
}

typedef struct { int i, l; } r_t; /* range used by radix tree */
typedef struct { char * s; r_t * r; } rm_t; /* used by cmp func */
typedef struct { char *s; r_t *g; t_t *t; a_t *a; int m, l, n, i, r; } rp_t;
/* packed, s: str, g: range, t: trie, a: AVL, len: g=m t=l a=n, retrieve: i,r */
int /* compare when searching */
rs(int c, int ri, void * u) { /* c: character, ri: index of range */
  char * s = ((rm_t *) u)->s; r_t * r = ((rm_t *) u)->r;
  return c - (r[ri].l ? s[r[ri].i] : 0);
} /* allow empty AVL node (range length = 0) */

int /* compare when inserting */
ri(int ra, int rb, void * u) { /* ra, rb: indice of range */
  char * s = ((rm_t *) u)->s; r_t * r = ((rm_t *) u)->r;
  return s[r[ra].i] - (r[rb].l ? s[r[rb].i] : 0);
} /* allow empty AVL node (range length = 0) */

int /* insert, z: i + size(tail) */
rins(int i, int d, rp_t * p) { char *s = p->s; r_t *g = p->g; t_t *t = p->t;
  a_t *a = p->a; int *m = &p->m, *l = &p->l, *n = &p->n;
  rm_t f[] = {s, g}; a_t * o = 0; r_t * k;
  int r = 0, b = 0, e = 0, z = i+strlen(s+i);
  while (*s && b == e && afet(s[i],&r,t[r].d,a,rs,f) && (o = a+r, r = o->d))
    for (k = g+o->k, b = k->i, e = b+k->l; b < e && s[b] == s[i]; ) b++, i++;
  b == e && !s[i] && (t[r].c = d, 1) || /* reached the trie node */
  o && e-b && (g[(*m)++] = (r_t) {b,e-b}, ains(*m-1,r,&t[*l].d,a,n,ri,f),
               g[(*m)++] = (r_t) {i,z-i}, ains(*m-1,*l+1,&t[*l].d,a,n,ri,f),
               o->d = *l, k->l -= e-b, t[*l+1].c = d, *l += 2) || /* fork */
  (t[*l].c = d, g[(*m)++] = (r_t) {i,z-i}, ains(*m-1,(*l)++,&t[r].d,a,n,ri,f));
} /* reached the trie root(trie[0]), insert new AVL node */
    /* i: index of range, r: index of AVL, c: copy, x: next, d: included */
int /* retrieve, 0 if the data does not exist or no children of included it */
rret(char c, rp_t * p) { char *s = p->s; r_t *g = p->g; t_t *t = p->t;
  a_t *a = p->a; int *m = &p->m, *l = &p->l, *n = &p->n, *i = &p->i, *r = &p->r;
  rm_t f[] = {s, g}; int o = * r, x, d = (o || (*i = 0), o && *i < g[a[o].k].l);
  return d && s[g[a[o].k].i+*i] == c && ++*i && *i == g[a[o].k].l || !d &&
      (!c || afet(c,&o,t[a[o].d].d,a,rs,f) && (*r=o, *i=1, *i == g[a[o].k].l)) ?
      (afet(0,&x,t[a[o].d].d,a,rs,f) ? t[a[x].d].c : t[a[o].d].c) : 0;
} /* if included & reached last character | !included & (EOF | goto next AVL) */
  /*   data is in this AVL node or next empty AVL node                        */
int
cmp(const void * a, const void * b) {
  char * x = * ((char **) a) + 2, * y = * ((char **) b) + 2;
  while (* x == * y && * x) x++, y++;
  return * x - * y;
}

typedef enum { RADIX_TREE, TRIE, AVL_TREE } draw_t;
int draw(draw_t type, const char * format, rp_t p);

#define P(func) ((d = func) ? d : '#') /* patch char */

int
main(void) {
  char * rhs[] = {"E:U","U:T","U:U+T","T:V","V:F","V:V*F","F:i","F:(E)"};
  int i, l = sizeof(rhs)/sizeof(*rhs);
  /*qsort(rhs, sizeof(char *), l, cmp);*/
  /*for (i = 0; i < l; i++) puts(rhs[i]);*/
  rp_t p = {0,(r_t[100]){0},(t_t[100]){0},(a_t[100]){0},0,1,1,0,0};
  int r = 0, d;
  /* test trie by assigning long sentances to trie */
  /* radix tree used memory: 8*(n-g+1)+20*(n-g+1)+8*(n-g)
   * trie used memory:       8*(n+1)+20*(n+1)
   * n: number of nodes, g: number of nodes can be grouped *//*
  char * test[] = {"romane","romanus","romulus","rubens","ruber","rubicon",
    "rubicundus","a","to","too","v","vo",""};
  for (p.s = *test, i = 0; i <= 20 && i < sizeof(test)/sizeof(*test); i++)
    rins(test[i]-*test, i+1, &p);
  printf("  has a(%d): %d\n",   r, rret('a',  &p)), r = p.r = 0;
  printf("  has (%d): %d\n",    r, rret('\0', &p)), r = p.r = 0;
  printf("  has v(%d): %d\n",   r, rret('v',  &p)), r = p.r;
  printf("  has v(%d): %d\n",   r, rret('\0', &p)), r = p.r;
  printf("  has v(%d): %d\n",   r, rret('\0', &p)), r = p.r = 0;
  printf("  has to(%d): %d\n",  r, rret('t',  &p)), r = p.r;
  printf("  has to(%d): %d\n",  r, rret('o',  &p)), r = p.r;
  printf("  has to(%d): %d\n",  r, rret('\0', &p)), r = p.r;
  printf("  has to(%d): %d\n",  r, rret('\0', &p)), r = p.r = 0;
  printf("  has too(%d): %d\n", r, rret('t',  &p)), r = p.r;
  printf("  has too(%d): %d\n", r, rret('o',  &p)), r = p.r;
  printf("  has too(%d): %d\n", r, rret('o',  &p)), r = p.r;
  printf("  has too(%d): %d\n", r, rret('\0', &p)), r = p.r = 0;
  draw(RADIX_TREE, "%d", p);
  */
  /*
  for (p.s = *test, i = 0; i <= 19 && i < sizeof(test)/sizeof(*test); i++)
    tmap(test[i], i+1, p.t, p.a, &p.l, &p.n);
  draw(TRIE, "%d", p);
  */
  /* test trie by map a string to a character *//*
  for (i = 0; i < l; i++) tmap(rhs[i]+2, *rhs[i], p.t, p.a, &p.l, &p.n);
  printf("  has U(%d): %c\n",   r, P(tret('U',  &r, p.t, p.a)));
  printf("  has U(%d): %c\n",   r, P(tret('\0', &r, p.t, p.a)));
  printf("  has U(%d): %c\n",   r, P(tret('\0', &r, p.t, p.a))), r = 0;
  printf("  has U+T(%d): %c\n", r, P(tret('U',  &r, p.t, p.a)));
  printf("  has U+T(%d): %c\n", r, P(tret('+',  &r, p.t, p.a)));
  printf("  has U+T(%d): %c\n", r, P(tret('T',  &r, p.t, p.a))), r = 0;
  printf("  has UF(%d): %c\n",  r, P(tret('U',  &r, p.t, p.a)));
  printf("  has UF(%d): %c\n",  r, P(tret('F',  &r, p.t, p.a))), r = 0;
  printf("  has (E)(%d): %c\n", r, P(tret('(',  &r, p.t, p.a)));
  printf("  has (E)(%d): %c\n", r, P(tret('E',  &r, p.t, p.a)));
  printf("  has (E)(%d): %c\n", r, P(tret(')',  &r, p.t, p.a))), r = 0;
  printf("  has V*F(%d): %c\n", r, P(tret('V',  &r, p.t, p.a)));
  printf("  has V*F(%d): %c\n", r, P(tret('*',  &r, p.t, p.a)));
  printf("  has V*F(%d): %c\n", r, P(tret('F',  &r, p.t, p.a))), r = 0;
  printf("  has V*D(%d): %c\n", r, P(tret('V',  &r, p.t, p.a)));
  printf("  has V*D(%d): %c\n", r, P(tret('*',  &r, p.t, p.a)));
  printf("  has V*D(%d): %c\n", r, P(tret('D',  &r, p.t, p.a))), r = 0;
  draw(TRIE, "%c", p);
  */
  /* test trie by assigning number to trie node data *//*
  char str[1] = {'\x00'};
  tins(str, p.t, p.a, &p.l, &p.n);
  tins(str, p.t, p.a, &p.l, &p.n);
  tins(str, p.t, p.a, &p.l, &p.n);
  tins("\x09\x08", p.t, p.a, &p.l, &p.n);
  tins("\x09\x08", p.t, p.a, &p.l, &p.n);
  tins(str, p.t, p.a, &p.l, &p.n);
  tins("\x09\x06", p.t, p.a, &p.l, &p.n);
  tins("\x09\x07", p.t, p.a, &p.l, &p.n);
  tins("\x08\x07", p.t, p.a, &p.l, &p.n);
  printf("  has 0(%d): %d\n",   r, tnex('\0',   &r, p.t, p.a));
  printf("  has 8 7(%d): %d\n", r, tnex('\x08', &r, p.t, p.a));
  printf("  has 8 7(%d): %d\n", r, tnex('\x07', &r, p.t, p.a)), r = 0;
  printf("  has 9 9(%d): %d\n", r, tnex('\x09', &r, p.t, p.a));
  printf("  has 9 9(%d): %d\n", r, tnex('\x09', &r, p.t, p.a)), r = 0;
  printf("  has 9 7(%d): %d\n", r, tnex('\x09', &r, p.t, p.a));
  printf("  has 9 7(%d): %d\n", r, tnex('\x07', &r, p.t, p.a)), r = 0;
  printf("  has 9 8(%d): %d\n", r, tnex('\x09', &r, p.t, p.a));
  printf("  has 9 8(%d): %d\n", r, tnex('\x08', &r, p.t, p.a)), r = 0;
  printf("  has 9 6(%d): %d\n", r, tnex('\x09', &r, p.t, p.a));
  printf("  has 9 6(%d): %d\n", r, tnex('\x06', &r, p.t, p.a)), r = 0;
  */
  /* test AVL tree */
  ains(8, 0, &r, p.a, &p.n, tm, 0);
  ains(3, 0, &r, p.a, &p.n, tm, 0);
  ains(4, 0, &r, p.a, &p.n, tm, 0);
  ains(7, 0, &r, p.a, &p.n, tm, 0);
  ains(6, 0, &r, p.a, &p.n, tm, 0);
  printf("  fetch 0: %d\n", afet(0, &d, r, p.a, tm, 0));
  printf("  fetch 1: %d\n", afet(1, &d, r, p.a, tm, 0));
  printf("  fetch 2: %d\n", afet(2, &d, r, p.a, tm, 0));
  printf("  fetch 3: %d\n", afet(3, &d, r, p.a, tm, 0));
  printf("  fetch 4: %d\n", afet(4, &d, r, p.a, tm, 0));
  printf("  fetch 5: %d\n", afet(5, &d, r, p.a, tm, 0));
  printf("  fetch 6: %d\n", afet(6, &d, r, p.a, tm, 0));
  printf("  fetch 7: %d\n", afet(7, &d, r, p.a, tm, 0));
  printf("  fetch 8: %d\n", afet(8, &d, r, p.a, tm, 0));
  printf("  fetch 9: %d\n", afet(9, &d, r, p.a, tm, 0));
  draw(AVL_TREE, "%d", p);
  return 0;
}

int draw(draw_t type, const char * format, rp_t p) {
  printf("Used memory: [trie %zu] * %d + [AVL node %zu] * %d = %zu\n",
         sizeof(t_t), p.m, sizeof(a_t), p.l, p.m*sizeof(t_t)+p.n*sizeof(a_t));
  Agraph_t * g = agopen("g", Agdirected, 0);
  Agnode_t * tn[100], * an[100];
  Agedge_t * e;
  GVC_t * gvc = gvContext();
  char buf[900] = {0}; int i, bi = 0, m, d;
  agsafeset(g, "rankdir", "LR", "");
  for (i = 0; type != AVL_TREE && i < p.l; i++)
    m = sprintf(buf+bi, "t%0X", i)+1,
    tn[i] = agnode(g, buf+bi, 1), bi += m,
    type == RADIX_TREE || type == TRIE && (
        p.t[i].c && (m = sprintf(buf+bi, format, p.t[i].c)+1,
                     agsafeset(tn[i], "label", buf+bi, ""), bi += m) ||
        agsafeset(tn[i], "label", "", "")),
    agsafeset(tn[i], "colorscheme", "ylgn9", ""),
    p.t[i].c && agsafeset(tn[i], "fillcolor", "4", ""),
    agsafeset(tn[i], "shape", "rectangle", ""),
    agsafeset(tn[i], "style", "rounded,filled", ""),
    agsafeset(tn[i], "fixedsize", "true", ""),
    agsafeset(tn[i], "fontname", "Sans", "");
  for (i = 0; i < p.n; i++)
    m = sprintf(buf+bi, "a%0X", i)+1,
    an[i] = agnode(g, buf+bi, 1), bi += m,
    type == RADIX_TREE && (m = sprintf(buf+bi, "%.*s", i ? p.g[p.a[i].k].l : 1,
                                       i ? p.s+p.g[p.a[i].k].i : "#")+1),
    type == TRIE && (m = sprintf(buf+bi, "%c", P(p.a[i].k))+1),
    type == AVL_TREE && (m = sprintf(buf+bi, "%d", p.a[i].k)),
    agsafeset(an[i], "label", buf+bi, ""), bi += m,
    agsafeset(an[i], "shape", "circle", ""),
    agsafeset(an[i], "fontname", "Sans", ""),
    agsafeset(an[i], "colorscheme", "blues9", ""),
    agsafeset(an[i], "fillcolor", "4", ""),
    agsafeset(an[i], "style", "filled", "");
  for (i = 0; i < p.l; i++)
    p.t[i].d && (e = agedge(g, tn[i], an[p.t[i].d], 0, 1),
                 agsafeset(e, "arrowhead", "none", ""));
  for (i = 0; i < p.n; i++)
    p.a[i].l && (e = agedge(g, an[i], an[p.a[i].l], 0, 1),
                 agsafeset(e, "colorscheme", "blues9", ""),
                 agsafeset(e, "color", "7", "")),
    p.a[i].r && (e = agedge(g, an[i], an[p.a[i].r], 0, 1),
                 agsafeset(e, "colorscheme", "blues9", ""),
                 agsafeset(e, "color", "7", "")),
    type != AVL_TREE && (e = agedge(g, an[i], tn[p.a[i].d], 0, 1),
                         agsafeset(e, "arrowhead", "none", ""));
  gvLayout(gvc, g, "dot");
  gvRenderFilename(gvc, g, "png", "graphviz.png");
  gvFreeLayout(gvc, g);
  agclose(g);
}
