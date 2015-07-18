#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>
#include <time.h>

#define SMAXT(t) ((t)0x7<<sizeof(t)*8-4|((t)0x1<<sizeof(t)*8-4)-(t)1)
#define UMAXT(t) ((t)0xF<<sizeof(t)*8-4|((t)0x1<<sizeof(t)*8-4)-(t)1)

typedef int dl_t; /* sizeof(dl_t) is normally >= sizeof(dt_t) */
typedef struct { dl_t b, c; } d_t;
typedef unsigned char dt_t;
typedef int dd_t;
/*                    *//* dt_t: If your character is ascii code, use char    */
#define DS sizeof(d_t)  /*       If it is binary(eg. utf8), use unsigned char */
#define DT sizeof(dt_t) /*       If it is unicode point, use unsigned short   */
#define DD sizeof(dd_t) /*       The default is unsigned char                 */
#define DX SMAXT(dl_t)  /*       0xFF..FF(-1) is used as terminator in tail,  */
#define DM UMAXT(dt_t)  /*       so -1 can not be used as character value     */
/*                    *//* dd_t: Depending on what user want to stored,       */
d_t * /*              *//*       the value can be a number or a struct,       */
dini(dl_t l) { /*     *//*       and its size can vary from 1 to 8 or more    */
  if (!l) return 0; /**//*       bytes. The default is int                    */
  d_t * d = malloc(l*DS+DS); dl_t i;
  for (d[0] = (d_t){0,-1}, i = 1; d[i] = (d_t){i-1,-i-1}, i != l; i++);
  return d[1].b = l, d[l].c = -1, d;
}

int
drea(d_t ** d, dl_t * l) {
  dl_t i, b = *l, e, f, m; d_t * n = *d;
  if (b > DX - b || !(e = b*2+1, i = ++b)) return 1; /* len is max */
  if (!(n = realloc(n, DS*(*l = e)+DS))) return 2; /* realloc error */
  for (*d = n, f = n->c; n[i] = (d_t){i-1,-i-1}, i != e; i++);
  m = f ? (n[n[b].b = n[-f].b].c = -b, -f) : (n->c = -b, b);
  n[n[m].b = e].c = -m;
  return 0;
}

int
dbas(dl_t * a, dl_t n, d_t ** d, dl_t * l) {
  int e = 0; dl_t i = 0, j = 1, w;
  for (; (-i[*d].c > i || !(e=drea(d,l))) && (i = -i[*d].c) < a[0];);
  for (; !e & j < n && (-i[*d].c > i || !(e=drea(d,l))); j<n &&(i=-i[*d].c))
    for (j = 1; j < n; j++) {
      for (w = a[j]-a[0]; w > *l-i;) if (e = drea(d, l)) return -e;
      if ((*d)[i+w].c >= 0) break;
    }
  return e ? -e : i-a[0];
}

int /* faster */
dBas(dl_t * a, dl_t n, d_t ** d, dl_t * l) {
  int e = 0; dl_t i = 0, j, b, w;
  for (;;) {
    if (-i[*d].c <= i && (e = drea(d,l))) return -e;
    if ((b = (i = -i[*d].c) - a[0]) >= 0) if (n == 1) return b; else break;
  }
  for (;; b = (i = -i[*d].c) - a[0]) {
    if (-i[*d].c <= i && (e = drea(d,l))) return -e;
    for (j = 1;;) {
      for (w = a[j]; w > *l-b;) if (e = drea(d, l)) return -e;
      if ((*d)[b+w].c >= 0) break;
      if (++j == n) return b;
    }
  }
}

void
drel(dl_t s, dl_t b, dl_t nb, dl_t * a, dl_t n, d_t * d, dl_t l) {
  dl_t i, j = 0, m, c, t, u, kb, k, p, h, e, x; /* e: end, x: max size */
  for (d[s].b = nb, i = 0; i < n; i++) {
    t = b + (c = a[i]), u = nb + c, d[p = d[u].b].c = k = d[u].c, d[-k].b = p,
    p > u && (d->c = k) || p == u && (d->c = 0), d[u] = (d_t){kb = d[t].b,s};
    for (; (k = -d[j].c) > j && k < t; j = k);
    if (j) d[d[k].b = t] = (d_t){j,-k}, d[j].c = -t;
    else if (k) d[e = d[k].b, d[k].b = t] = (d_t){e,-k}, d[e].c = d->c = -t;
    else d[t] = (d_t){t,d->c = -t};
    if (j = t, kb >= 0) for (x = DM + (DX > DM), m = 1; d[h = kb+m].c == t &&
                             (d[h].c = u), m != x && h != l; m++);
  }
}

dt_t *
dinl(dl_t c) { return calloc(DT, c); }

int
dral(dt_t ** t, dl_t * c) {
  dt_t * n; dl_t b = *c, e;
  if (*c > DX - *c) return 3; /* no enough space to add tail */
  if (n = realloc(*t, DT*(e = *c<<=1))) *t = n; else return 2;
  for (; b < e; b++) n[b] = 0;
  return 0;
}

#define DBAS(a, n) do {if ((nb = dBas(a,n,&d,l))<0) return -nb;*rd = d;}while(0)
#define DJMP(nb, tc) t = nb + tc, d[p = d[t].b].c = k = d[t].c, d[-k].b = p, \
                     p > t && (d->c = k) || p == t && (d->c = 0), d[t].c = s
#define DSTR(a, n) do { for (x += y, j = 0; j < n && (j[x] = j[a] + 1); j++); \
                        *(dd_t*)(x+n+1)=g, *vl+=n+1+DD, d[t].b = ~y; } while(0)

int /* v: tail, u: max, g: data, r: remain */
dins(dt_t *a, dl_t n, dd_t g, d_t **rd, dl_t *l, dt_t **v, dl_t *vl, dl_t *vc) {
  dl_t i,j,s,c,tc,b,nb,t,k,m,p, y,w, h,h1[DM],h2[DM],l1,l2,li, *z, u, r;
  d_t *d; int e; dt_t *x;
  for (i = 0, s = 0, x = *v, y = *vl, d = *rd;;) {
    if ((b = d[s].b) < 0) { /* a[i](signed) should < DM */
      for (x += ~b, a += i, n -= i, j = 0;;) {
        if (j == n) return x[n] != 0 || (*(dd_t*)(x+n+1)=g),4;
        if (tc = x[j], c = a[j++]+1, tc != c) break;
        z = (dl_t[]){c}; DBAS(z, 1); d[s].b = nb, DJMP(nb, c), s = t;
      }
      for (x=*v; n>=(r=*vc-y) || n+DD>=r;) if (e=dral(v,vc),x=*v,e) return e;
      if (tc) { z = (dl_t[]){tc,c}; DBAS(z, 2); DJMP(nb, tc), d[t].b = b-j; }
      else    { z = (dl_t[]){c};    DBAS(z, 1); }
      d[s].b = nb, DJMP(nb, c), a += j, n -= j; DSTR(a, n); return 0;
    }
    if (i == n) return 4; /* the inserted key is a prefix of another key */
    for (c = a[i++] + 1; c > *l-b;) if (e = drea(rd, l), d = *rd, e) return -e;
    if ((k = d[t = b + c].c) != s) {
      for (w=n-i; w>=(r=*vc-y) || w+DD>=r;) if (e=dral(v,vc),x=*v,e) return e;
      if (k >= 0 && (u = DM + (DX > DM))) {
        for (l1 = 0, j = 1; (d[h = b+j].c == s || j == c && (li = l1, 1)) &&
             (h1[l1++] = j), j != u && h != *l; j++);
        for (l2 = 0, j = 1, m = d[k].b; d[h = m+j].c == k && (h2[l2++] = j),
             j != u && h != *l; j++);
        if (l1 <= l2) {
          DBAS(h1, l1);
          for (j = li+1; j < l1; j++) h1[j-1] = h1[j];
          drel(s, b, nb, h1, --l1, d, *l), b = nb;
        } else {
          DBAS(h2, l2);
          drel(k, m, nb, h2, l2, d, *l), s = d[b+(h1[0] == c ? h1[1]:h1[0])].c;
        }
      }
      DJMP(b, c), a += i; DSTR(a, w); return 0;
    }
    s = t; /* success */
  }
}

int /* g: data */
dlok(dt_t * a, dl_t n, dd_t * g, d_t * d, dl_t l, dt_t * v) {
  dl_t i = 0, j, s = 0, c, b, t;
  for (;; s = t) {
    if ((b = d[s].b) < 0) for (v += ~b, a += i, n -= i, j = 0;; j++)
      if (j == n) return v[n] != 0 || (*g = *(dd_t*)(v+n+1),0);
      else if (v[j] != a[j] + 1) return 1;
    if (i == n) return 1; /* the inserted key is a prefix of another key */
    if ((c = a[i++] + 1) > l-b) return 2;  /* a[i](signed) should < DM */
    if (d[t = b + c].c != s) return 1;
  }
}

const char * const DR[] = {"success", "len is max", "realloc err",
  "no enough space to add tail", "the inserted key is a prefix or duplicated"};

int
wda(FILE * f, char * s, d_t * d, dl_t l) {
  int j, k;
  for (s && puts(s), j = 0;;) {
    for (k = 0; fprintf(f, "%5d", j+k), k < 31 && j+k < l; k++); fputc('\n', f);
    for (k = 0; fprintf(f, "-----"), k < 31 && j+k < l; k++); fputc('\n', f);
    for (k = 0; fprintf(f, "%5d", d[j+k].b), k < 31 && j+k < l; k++);
    fputc('\n', f);
    for (k = 0; fprintf(f, "%5d", d[j+k].c), k < 31 && j+k < l; k++);
    fputc('\n', f), fputc('\n', f);
    if ((j+=k+1)-1 == l) break;
  }
}

int
fda(char * s, d_t * d, dl_t l) {
  FILE * f = fopen(s, "w"); wda(f, 0, d, l), fclose(f);
}

int
pda(char * s, d_t * d, dl_t l) { wda(stdout, s, d, l); return 0; }

#define DL(a) (sizeof(a)/sizeof(*a))
#define GOOD "\e[1;32mgood\e[0m"
#define BAD "\e[1;31mbad\e[0m"

int /* r: return, e: expected, m: message */
test(int r, int e, const char * m) {
  if (r == e) {
    printf("  "GOOD); return 0;
  } else {
    printf("\n  "BAD), m && printf("  %s", m) ||
    printf("  %d should eq %d", r, e); return 1;
  }
}

void
test_dcmp(d_t * a, dl_t al, d_t * b, dl_t bl) {
  int e = 1; dl_t i;
  if (al == bl)
    for (i = 0; ; i++) {
      if (a[i].b != b[i].b || a[i].c != b[i].c) {
        e = 0;
        break;
      }
      if (i == al) break;
    }
  else e = 0;
  e && printf("  "GOOD) || (pda("\n  "BAD, a, al), pda("\n  should eq", b, bl));
}

void
test_dini1(void) {
  dl_t l = 0; d_t * d = dini(l);
  printf("test dini: cannot init with len = 0");
  test(d == 0, 1, "the pointer of double array should eq 0"), puts("");
}

void
test_dini2(void) {
  dl_t l = 1; d_t * d = dini(l), e[] = {{0,-1},{1,-1}};
  printf("test dini: can init with len >= 1");
  test_dcmp(d, l, e, DL(e)-1), free(d), puts("");
}

void
test_drea1(void) {
  dl_t l = 1; d_t * d = dini(l), e[] = {{0,-1},{3,-2},{1,-3},{2,-1}};
  printf("test drea: no cells occupied"), drea(&d, &l);
  test_dcmp(d, l, e, DL(e)-1), free(d), puts("");
}

void
test_drea2(void) {
  dl_t l = 3; d_t * d = dini(l), e[] = {{0,-1},{7,-2},{1,-4},{0,0},
    {2,-5},{4,-6},{5,-7},{6,-1}};
  printf("test drea: last cell occupied"), d[1].b = 2, d[3] = (d_t){0,0};
  drea(&d, &l), test_dcmp(d, l, e, DL(e)-1), free(d), puts("");
}

void
test_drea3(void) {
  dl_t l = 1; d_t * d = dini(l), e[] = {{0,-2},{0,0},{3,-3},{2,-2}};
  printf("test drea: all cells occupied"), d[0].c = 0, d[1] = (d_t){0,0};
  drea(&d, &l), test_dcmp(d, l, e, DL(e)-1), free(d), puts("");
}

void
test_dBas1(void) {
  dl_t l = 1, a[] = {0}, n = DL(a); d_t * d = dini(l); int r;
  printf("test dBas: given {0}"), r = dBas(a, n, &d, &l);
  test(r, 1, "base should eq 1"), free(d), puts("");
}

void
test_dBas2(void) {
  dl_t l = 1, a[] = {1}, n = DL(a); d_t * d = dini(l); int r;
  printf("test dBas: given {1}"), r = dBas(a, n, &d, &l);
  test(r, 0, "base should eq 0"), free(d), puts("");
}

void
test_dBas3(void) {
  dl_t l = 1, a[] = {2}, n = DL(a); d_t * d = dini(l);
  printf("test dBas: given {2} when len < 2"), dBas(a, n, &d, &l);
  test(l, 3, "len should eq 3"), free(d), puts("");
}

#define DI SMAXT(dt_t)

void
test_dBas4(void) {
  dl_t l; d_t * d; int r;
  printf("test dBas: given {MAX}");
  if (!test(DX == DI, 1, "this test should be run with sizeof dl_t == dt_t")) {
    l = 1, d = dini(l), r = dBas((dl_t[]){DI}, 1, &d, &l);
    test(r, 0, "base should eq 0"), free(d);
  }
  puts("");
}

void
test_dBas5(void) {
  dl_t l; d_t * d; int r;
  printf("test dBas: given {MAX} when last cell is occupied");
  if (!test(DX == DI, 1, "this test should be run with sizeof dl_t == dt_t")) {
    l = DI, d = dini(l), d[1].b = l-1, d[l-1].c = -1, d[l].c = 0;
    r = dBas((dl_t[]){DI}, 1, &d, &l);
    test(r, -1, "should return error: len is max"), free(d);
  }
  puts("");
}

void
test_dBas6(void) {
  dl_t l = 3, a[] = {1,2}, n = DL(a); d_t * d = dini(l); int r;
  printf("test dBas: given {1,2}"), r = dBas(a, n, &d, &l);
  test(r, 0, "base should eq 0"), free(d), puts("");
}

void
test_dBas7(void) {
  dl_t l = 7, a[] = {1,3,5}, n = DL(a); d_t * d = dini(l); int r;
  printf("test dBas: given {1,3,5} when base[5] is occupied"), d[5].c = 0;
  r = dBas(a, n, &d, &l), test(r, 1, "base should eq 1"), free(d), puts("");
}

void
test_dBas8(void) {
  dl_t l = 1, a[] = {1,3}, n = DL(a); d_t * d = dini(l);
  printf("test dBas: given {1,3} when len < 3"), dBas(a, n, &d, &l);
  test(l, 3, "len should eq 3"), free(d), puts("");
}

void
test_dBas9(void) {
  dl_t l, * a, n; d_t * d; int r;
  printf("test dBas: given {1,MAX} when only last cell are unoccupied");
  if (!test(DX == DI, 1, "this test should be run with sizeof dl_t == dt_t")) {
    l = 1, a = (dl_t[]){1,DI}, n = 2, d = dini(l);
    dBas(a, n, &d, &l), test(l, DI, "len should eq MAX"),
    d->c = -DI, r = dBas(a, n, &d, &l);
    test(r, -1, "should return error: len is max"), free(d);
  }
  puts("");
}

void
test_dBas10(void) {
  dl_t i, l; d_t * d; int r;
  printf("test dBas: given {1,3,6} when base[1,3,5...MAX-2] are occupied");
  if (!test(DX == DI, 1, "this test should be run with sizeof dl_t == dt_t")) {
    l = DI, d = dini(l);
    for (i = 0; i < l-1; i+=2) d[i].c = -i-2, d[i+1].c = 0;
    r = dBas((dl_t[]){1,3,6}, 3, &d, &l);
    test(r, DI-6, "base should eq MAX-6"), free(d);
  }
  puts("");
}

void
test_dBas11(void) {
  dl_t i, l; d_t * d; int r;
  printf("test dBas: given {1,3,6,7} when base[1,3,5...MAX-2] are occupied");
  if (!test(DX == DI, 1, "this test should be run with sizeof dl_t == dt_t")) {
    l = DI, d = dini(l);
    for (i = 0; i < l-1; i+=2) d[i].b--, d[i].c = -i-2, d[i+1].c = 0;
    d[2].b = l, d[l].c = -2, r = dBas((dl_t[]){1,3,6,7}, 4, &d, &l);
    test(r, -1, "should return error: len is max (the key is out of bound)");
    free(d);
  }
  puts("");
}

void
test_drel1(void) {
  dl_t l = 4, a[] = {2}, n = DL(a);
  d_t d[] = {{1,-1},{4,-2},{1,-4},{-1,0},{2,-1}},
      e[] = {{0,-1},{4,-3},{-1,0},{1,-4},{3,-1}};
  printf("test drel: given {2} when base+2 is in the middle of double array");
  drel(0, d[0].b, 0, a, n, d, l), test_dcmp(d, l, e, DL(e)-1), puts("");
}

void
test_drel2(void) {
  dl_t l = 3, a[] = {1}, n = DL(a);
  d_t d[] = {{0,-2},{-1,0},{3,-3},{2,-2}}, e[] = {{1,-1},{3,-3},{-1,0},{1,-1}};
  printf("test drel: given {1} when the new child is the first empty cell");
  drel(0, d[0].b, 1, a, n, d, l), test_dcmp(d, l, e, DL(e)-1), puts("");
}

void
test_drel3(void) {
  dl_t l = 3, a[] = {1}, n = DL(a);
  d_t d[] = {{0,-2},{-1,0},{2,-2},{-1,1}}, e[] = {{1,-1},{1,-1},{-1,0},{-1,1}};
  printf("test drel: given {1} when the new child is the final empty cell");
  drel(0, d[0].b, 1, a, n, d, l), test_dcmp(d, l, e, DL(e)-1), puts("");
}

void
test_drel4(void) {
  dl_t l = 3, a[] = {1}, n = DL(a);
  d_t d[] = {{1,-1},{1,-1},{-1,0},{-1,1}}, e[] = {{0,-2},{-1,0},{2,-2},{-1,1}};
  printf("test drel: given {1} when there is one empty preceding the child");
  drel(0, d[0].b, 0, a, n, d, l), test_dcmp(d, l, e, DL(e)-1), puts("");
}

void
test_drel5(void) {
  dl_t l = 4, a[] = {1,3}, n = DL(a);
  d_t d[] = {{0,-2},{-1,0},{4,-4},{-2,0},{2,-2}},
      e[] = {{1,-1},{3,-3},{-1,0},{1,-1},{-2,0}};
  printf("test drel: given {1,3}");
  drel(0, d[0].b, 1, a, n, d, l), test_dcmp(d, l, e, DL(e)-1), puts("");
}

void
test_drel6(void) {
  dl_t l = 6, a[] = {1,4}, n = DL(a);
  d_t d[] = {{0,-2},{1,0},{-1,1},{6,-6},{3,0},{-2,4},{3,-3}},
      e[] = {{2,-1},{4,-4},{-1,3},{1,0},{1,-1},{-2,6},{3,0}};
  printf("test drel: given {1,4} when each node have one child");
  drel(0, d[0].b, 2, a, n, d, l), test_dcmp(d, l, e, DL(e)-1), puts("");
}

void
test_drel7(void) {
  dl_t l = 4, a[] = {1,2}, n = DL(a);
  d_t d[] = {{2,-1},{2,-2},{1,-1},{-1,0},{-2,0}},
      e[] = {{0,-3},{-1,0},{-2,0},{4,-4},{3,-3}};
  printf("test drel: given {1,2} when multiple child nodes move to front");
  drel(0, d[0].b, 0, a, n, d, l), test_dcmp(d, l, e, DL(e)-1), puts("");
}

void
test_drel8(void) {
  dl_t l, * a; d_t * d, * e;
  printf("test drel: given {1} when this node has a child: {UNSIGNED_MAX+1}");
  if (!test(DX > DI, 1, "this test should be run with sizeof dl_t > dt_t")) {
    l = DM+(DX > DI), (d=dini(l))->b = 2, (e=dini(l))->b = 0, d[d[4].b=2].c=-4;
    d[d[1].b = DM].c = -1, d[3] = (d_t){0,0}, d[DM+1] = (d_t){-1,3};
    e[e[2].b = DM].c = -2, e[1] = (d_t){0,0}, e[DM+1] = (d_t){-1,1}, e->c = -2;
    drel(0, d[0].b, 0, (dl_t[]){1}, 1, d, l), test_dcmp(d, l, e, l);
    free(d), free(e);
  }
  puts("");
}

void
test_dral1(void) {
  dl_t c = 1; dt_t * t = dinl(c), e[] = {0,0};
  printf("test dral: given {0}"), dral(&t, &c);
  test(memcmp(t, e, DL(e)*DT), 0, "tail should eq {0,0}"), free(t), puts("");
}

void
test_dral2(void) {
  dl_t c = 2; dt_t * t = dinl(c), e[] = {1,2,0,0};
  printf("test dral: given {1,2}");
  t[0] = 1, t[1] = 2, dral(&t, &c);
  test(memcmp(t, e, DL(e)*DT), 0, "tail should eq {1,2,0,0}"), free(t);
  puts("");
}

void
test_dins1(void) {
  dl_t l = 1, tl = 0, tc = 1;
  d_t * d = dini(l), e[] = {{0,0},{-1,0}}; dt_t a[] = {0}, * t = dinl(tc);
  printf("test dins: given {0}"), dins(a, DL(a), 0, &d, &l, &t, &tl, &tc);
  test_dcmp(d, l, e, DL(e)-1), free(d), free(t), puts("");
}

void
code(dt_t * a, dl_t n) { /* assume n >= 1 */
  while (--n, a[n] = a[n] ? a[n] - 'a' + 1 : 0, n);
}

int
wta(FILE * f, dt_t * a, dl_t n) {
  int j, k;
  for (j = 0; j < n; j += k) {
    for (k = 0; k < 32 && j+k < n; k++) fprintf(f, "%3d ", j+k);
    fputc('\n', f);
    for (k = 0; k < 32 && j+k < n; k++) fprintf(f, "----");
    fputc('\n', f);
    for (k = 0; k < 32 && j+k < n; k++)
      /*fprintf(f, "  %c  ", a[j+k] > 1 ? a[j+k]-1: a[j+k] == 1 ? '#' : '.');*/
      fprintf(f, "  %c ", a[j+k] > 1 ? a[j+k]+'a'-2: a[j+k] ? '#' : '.');
      /*fprintf(f, " %2d ", a[j+k] ? a[j+k]-1: 99);*/
    fputc('\n', f);
    if (j+k == n) break;
    fputc('\n', f);
  }
}

int
fta(char * s, dt_t * a, dl_t n) {
  FILE * f = fopen(s, "w"); wta(f, a, n), fclose(f);
}

int
pta(dt_t * a, dl_t n) { wta(stdout, a, n); }

void
test_tcmp(dt_t * a, dl_t al, dt_t * b, dl_t bl) {
  (al == bl && !memcmp(a, b, al)) && printf("  "GOOD) ||
      (puts("\n  "BAD), pta(a, al), puts("\n  should eq"), pta(b, bl));
}

void
test_dins2(void) {
  dl_t l = 1, tl = 0, tc = 1;
  d_t * d = dini(l), e[] = {{0,-1},{3,-3},{-1,0},{1,-1}};
  dt_t a[] = {1}, * t = dinl(tc), te[] = {0,0,0,0,0};
  printf("test dins: given {1}"), dins(a, DL(a), 0, &d, &l, &t, &tl, &tc);
  test_dcmp(d, l, e, DL(e)-1), test_tcmp(t, tl, te, DL(te)), free(d), free(t);
  puts("");
}

void /* base array + check array = double array */
dcat(dl_t * b, dl_t * c, d_t * d, dl_t n) { /* assume n >= 1 */
  while (--n, d[n] = (d_t){b[n],c[n]}, n);
}

void /* convert human readable string to tail */
tconv(dt_t * t, dl_t * n) {
  dl_t i, j; dl_t c;
  for (i = j = 0; i < *n; i += 3, j++)
    t[j] = (c=t[i])=='#' ? 1:(c=='.' ? 0:c-'a'+2);
  *n /= 3;
}

void
test_dins3(void) {
  dl_t l = 1, tl = 0, tc = 1, tn,
       /*       .   #   a   b   c   d   e   f   g   h   i   j   k   l   m   n */
       /*       0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15 */
       b1[] = { 0,  2,  1, -1},
       c1[] = {-1, -2, -1,  0},
       /*       0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15 */
       b2[] = { 0, 15,  1, -1,  2,  4,  5,  6,  7,  8,  9,-14, 10, 12, 13, 14},
       c2[] = {-1, -2, -4,  0, -5, -6, -7, -8, -9,-10,-12,  0,-13,-14,-15, -1},
       /*       0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15 */
       b3[] = { 0, 15,  0,  0, -3,-22,  1,  6,  7,  8,  9,-14, 10, 12, 13, 14},
       c3[] = {-1, -6,  3,  0,  2,  2, -7, -8, -9,-10,-12,  0,-13,-14,-15, -1},
       /*       0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15 */
       b4[] = { 3, 15,  0,-30, -3,-22,  0,  1,  7,  8,  9, 10, 11, 12,-14, 13},
       c4[] = {-1, -7,  6,  2,  2,  2,  0, -8, -9,-10,-11,-12,-13,-15,  0, -1};
  d_t * d = dini(l), e1[DL(b1)], e2[DL(b2)], e3[DL(b3)], e4[DL(b4)];
  dt_t a1[]="bachelor", a2[]="jar", a3[]="badge", a4[]="baby", n, *t = dinl(tc),
       te[] = /* 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20*/
           /**/ "a  c  h  e  l  o  r  #  .  .  .  .  .  a  r  #  .  .  .  .  . "
           /*   21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 */
           /**/" g  e  #  .  .  .  .  .  y  #  .  .  .  .  .  ";
  printf("test dins: given {bachelor#, jar#, badge#, baby#}");
  dcat(b1, c1, e1, DL(b1)), dcat(b2, c2, e2, DL(b2));
  dcat(b3, c3, e3, DL(b3)), dcat(b4, c4, e4, DL(b4));
  code(a1,n=DL(a1)), dins(a1,n,0,&d,&l,&t,&tl,&tc), test_dcmp(d,l,e1,DL(e1)-1);
  code(a2,n=DL(a2)), dins(a2,n,0,&d,&l,&t,&tl,&tc), test_dcmp(d,l,e2,DL(e2)-1);
  code(a3,n=DL(a3)), dins(a3,n,0,&d,&l,&t,&tl,&tc), test_dcmp(d,l,e3,DL(e3)-1);
  code(a4,n=DL(a4)), dins(a4,n,0,&d,&l,&t,&tl,&tc), test_dcmp(d,l,e4,DL(e4)-1);
  tn = DL(te), tconv(te,&tn), test_tcmp(t,tl,te,tn), free(d), free(t), puts("");
}

void
test_dins4(void) {
  dl_t l = 1, tl = 0, tc = 1;
  d_t * d = dini(l),
      e1[] = {{0,-1},{7,-5},{0,0},{-6,2},{-11,2},{1,-6},{5,-7},{6,-1}},
      e2[] = {{3,-1},{7,-2},{1,-7},{-6,5},{-11,5},{0,0},{-16,0},{2,-1}},
      e3[] = {{5,-1},{15,-2},{1,-6},{-6,7},{-11,7},{-21,7},{2,-9},{0,0},
        {-16,0},{6,-10},{9,-11},{10,-12},{11,-13},{12,-14},{13,-15},{14,-1}};
  dt_t a1[]={1}, a2[]={1,2}, a3[]={1,3}, a4[]={2}, a5[]={1,4}, * t = dinl(tc);
  printf("test dins: given {1},{1,2},{1,3},{2},{1,4}");
  dins(a1,DL(a1),0,&d,&l,&t,&tl,&tc), dins(a2,DL(a2),0,&d,&l,&t,&tl,&tc);
  dins(a3,DL(a3),0,&d,&l,&t,&tl,&tc), test_dcmp(d, l, e1, DL(e1)-1);
  dins(a4,DL(a4),0,&d,&l,&t,&tl,&tc), test_dcmp(d, l, e2, DL(e2)-1);
  dins(a5,DL(a5),0,&d,&l,&t,&tl,&tc), test_dcmp(d, l, e3, DL(e3)-1);
  free(d), free(t), puts("");
}

void
test_dins5(void) {
  dl_t l = 1, tl = 0, tc = 1;
  d_t * d = dini(l), e[] = {{0,-1},{1,-1},{0,0},{-6,2}};
  dt_t a1[] = {1}, a2[] = {1,2}, * t = dinl(tc); int r;
  printf("test dins: given {1},{1,2},{1,2},{1}");
  dins(a1,DL(a1),0,&d,&l,&t,&tl,&tc), dins(a2,DL(a2),0,&d,&l,&t,&tl,&tc);
  test_dcmp(d, l, e, DL(e)-1), r = dins(a1,DL(a1),0,&d,&l,&t,&tl,&tc);
  test(r, 4, "should return prefix key"), r=dins(a2,DL(a2),0,&d,&l,&t,&tl,&tc);
  test(r, 4, "should return duplicated key"), free(d), free(t), puts("");
}

void
test_dins6(void) {
  dl_t l = 1, tl = 0, tc = 1;
  d_t * d = dini(l); dt_t a[] = {1,2}, * t = dinl(tc); int r;
  printf("test dins: given {1,2},{1,2}");
  dins(a,DL(a),0,&d,&l,&t,&tl,&tc), r = dins(a,DL(a),0,&d,&l,&t,&tl,&tc);
  test(r, 4, "should return duplicated key"), free(d), free(t), puts("");
}

void
test_dins7(void) {
  dl_t l = 1, tl = 0, tc = 1; int r;
  d_t * d = dini(l); dt_t a1[]={1}, a2[]={2}, * t = dinl(tc), te[2+DD*2] = {0};
  printf("test dins: given {1 => 123}, {2 => 234}");
  dins(a1,DL(a1),123,&d,&l,&t,&tl,&tc); dins(a2,DL(a2),234,&d,&l,&t,&tl,&tc);
  *(dd_t*)(te+1) = 123, *(dd_t*)(te+1+DD+1) = 234, test_tcmp(t, tl, te, DL(te));
  free(d), free(t), puts("");
}

void
test_dlok1(void) {
  dl_t l = 1, tl = 0, tc = 1; dd_t g;
  d_t * d = dini(l); dt_t a1[] = {}, a2[] = {l+1}, * t = dinl(tc); int r;
  printf("test dlok: given {}, {l+1}"), r = dlok(a1,DL(a1),&g,d,l,t);
  test(r, 1, "should return not found error"), r = dlok(a2,DL(a2),&g,d,l,t);
  test(r, 2, "should return key is out of bound error");
  free(d), free(t), puts("");
}

void
test_dlok2(void) {
  dl_t l = 1, tl = 0, tc = 1; dd_t g;
  d_t * d = dini(l); dt_t a[] = {0}, * t = dinl(tc); int r;
  printf("test dlok: given {0} when {0}");
  dins(a,DL(a),0,&d,&l,&t,&tl,&tc), r = dlok(a,DL(a),&g,d,l,t);
  test(r, 0, "should found the key"), free(d), free(t), puts("");
}

void
test_dlok3(void) {
  dl_t l = 1, tl = 0, tc = 1; dd_t g;
  d_t * d = dini(l); dt_t a1[] = {0,1,2}, b1[] = {0}, b2[] = {0,1},
      b3[] = {0,1,2,3}, * t = dinl(tc); int r;
  printf("test dlok: given {0},{0,1},{0,1,2},{0,1,2,3} when {0,1,2}");
  dins(a1,DL(a1),0,&d,&l,&t,&tl,&tc);
  r = dlok(b1,DL(b1),&g,d,l,t), test(r, 1, "should return not found error");
  r = dlok(b2,DL(b2),&g,d,l,t), test(r, 1, "should return not found error");
  r = dlok(a1,DL(a1),&g,d,l,t), test(r, 0, "should found the key");
  r = dlok(b3,DL(b3),&g,d,l,t), test(r, 1, "should return not found error");
  free(d), free(t), puts("");
}

void
test_dlok4(void) {
  dl_t l = 1, tl = 0, tc = 1; dd_t g;
  d_t * d = dini(l); dt_t a1[] = {2,4,0}, a2[] = {4,1,0}, a3[] = {4,2,3,0},
      b1[] = {1,3,0}, b2[] = {2,4}, b3[] = {4,1,3}, * t = dinl(tc); int r;
  printf("test dlok: given {1,3,0},{2,4},{4,1,3} if {2,4,0},{4,1,0},{4,2,3,0}");
  dins(a1,DL(a1),0,&d,&l,&t,&tl,&tc); dins(a2,DL(a2),0,&d,&l,&t,&tl,&tc);
  r = dins(a3,DL(a3),0,&d,&l,&t,&tl,&tc);
  r = dlok(b1,DL(b1),&g,d,l,t), test(r, 1, "should return not found error");
  r = dlok(b2,DL(b2),&g,d,l,t), test(r, 1, "should return not found error");
  r = dlok(b3,DL(b3),&g,d,l,t), test(r, 1, "should return not found error");
  r = dlok(a1,DL(a1),&g,d,l,t), test(r, 0, "should found the key");
  r = dlok(a2,DL(a2),&g,d,l,t), test(r, 0, "should found the key");
  r = dlok(a3,DL(a3),&g,d,l,t), test(r, 0, "should found the key");
  free(d), free(t), puts("");
}

/* Usage for evaluation: $ ./datrie input_file
 * File: datrie.c.in.1, The reserved words for Pascal
 * File: datrie.c.in.2, The reserved words for COBOL
 * File: datrie.c.in.3, A listing of Linux RPMs
 * File: datrie.c.in.4, First Level Administrations of All Countries
 * File: datrie.c.in.5, Katakana for a Japanese word dictionary [1]
 *
 * [1] http://dictionary.goo.ne.jp/thsrs/
 */

void  /* m: max string length, e: elapsed time */
eval(int argc, char ** argv) { /* iw: insert worst time, ia: insert average T */
  FILE * f; size_t i, j, k, l, m, n; clock_t e, iw, ia, lw, la;
  dl_t dl, tl, tc;
  d_t * d; dt_t * s, * t; dd_t g; int r, rt;
  f = fopen(argv[1], "r"); if (!f) { perror(argv[1]); return; }
  for (iw = ia = lw = la = 0, k = 0, r = 0, n = 50;;) {
    if (fscanf(f, "%zu%zu\n", &l, &m)-2) break;
    dl = 1, tl = 0, tc = 1, d = dini(dl), t = dinl(tc);
    s = calloc(m/sizeof(int)*sizeof(int)+(m%sizeof(int)?sizeof(int):0),1);
    for (e = clock(), i = j = 0; i < l; i++) {
      if (fscanf(f, "%[^\n]\n", s) == -1) { r = -1; break; }
      if (r = dins(s,strlen(s)+1,0,&d,&dl,&t,&tl,&tc)) break;
      /*if (i > j) putchar('i'), fflush(stdout), j += l / 10;*/
    }
    e = clock() - e, ia += e, e > iw && (iw = e), rewind(f);
    /*printf("base %d\n", d[597].b);*/
    /*fda("datrie.debug.final", d, dl);*/
    if (fscanf(f, "%zu%zu\n", &l, &m)-2) break;
    for (e = clock(), i = j = 0; i < l; i++) {
      if (fscanf(f, "%[^\n]\n", s) == -1) { r = -1; break; }
      if (r = dlok(s,strlen(s)+1,&g,d,dl,t)) break;
      /*if (i > j) putchar('l'), fflush(stdout), j += l / 10;*/
    }
    e = clock() - e, la += e, e > lw && (lw = e), rewind(f)/*, putchar('\n')*/;
    if (++k < n && !r) free(d), free(t), free(s); else break;
    putchar('.'), fflush(stdout);
  }
  putchar('\n');
  if (r) printf("return %d, i %zu  [%s]\n", r, i, s);
  for (i = dl; i > 0 && d[i].c < 0; i--); i++;
  printf("KEY_NUM               %10zu\n"
         "SPACE_DOUBLE          %10zu bytes\n"
         "SPACE_TAIL            %10zu bytes\n"
         "SPACE_DOUBLE_TAIL     %10zu bytes\n"
         "SPACE_SOURCE          %10zu bytes\n"
         "insert time - worst   %10lf ms\n"
         "insert time - average %10lf ms\n"
         "lookup time - worst   %10lf ms\n"
         "lookup time - average %10lf ms\n", l, i*DS, tl*DT, i*DS+tl*DT,
         (fseek(f, 0L, SEEK_END), ftell(f)),
         (double) iw * 1000 / CLOCKS_PER_SEC,
         (double) ia * (1000 / n) / CLOCKS_PER_SEC,
         (double) lw * 1000 / CLOCKS_PER_SEC,
         (double) la * (1000 / n) / CLOCKS_PER_SEC);
  free(d), free(t), free(s), fclose(f);
}

int
main(int argc, char ** argv) {
  if (argc < 2) {
    test_dini1();
    test_dini2();
    test_drea1();
    test_drea2();
    test_drea3();
    test_dBas1();
    test_dBas2();
    test_dBas3();
    test_dBas4();
    test_dBas5();
    test_dBas6();
    test_dBas7();
    test_dBas8();
    test_dBas9();
    test_dBas10();
    test_dBas11();
    test_drel1();
    test_drel2();
    test_drel3();
    test_drel4();
    test_drel5();
    test_drel6();
    test_drel7();
    test_drel8();
    test_dral1();
    test_dral2();
    test_dins1();
    test_dins2();
    test_dins3();
    test_dins4();
    test_dins5();
    test_dins6();
    test_dins7();
    test_dlok1();
    test_dlok2();
    test_dlok3();
    test_dlok4();
  } else {
    eval(argc, argv);
  }
  return 0;
}
