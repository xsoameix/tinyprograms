#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TLEN 100 + 1
#define PLEN 1000

typedef struct {
  char t[TLEN];
  char p[PLEN][TLEN];
  int occur[PLEN];
} work;

work *
work_new(void) {
  work * w = calloc(1, sizeof(work));
  memset(&w->occur, -1, sizeof(w->occur));
  return w;
}

void
work_del(work * w) { free(w); }

#define CLEN 26 /* A-Z a-z */
#define LENOF(s) (sizeof(s) / sizeof(s[0]))

typedef struct trie {
  struct trie * l[CLEN], * suffix, * dsuffix;
  int id;
} trie;

trie *
trie_new(void) {
  trie * t = calloc(1, sizeof(trie));
  t->id = -1;
  return t;
}

void
trie_del(trie * t) {
  int i, len = LENOF(t->l);
  for (i = 0; i < len; i++)
    if (i[t->l]) trie_del(i[t->l]);
  free(t);
}

/* char to int */
#define C2I(c) (c >= 'a' ? c - 'a' : c - 'A')

void
trie_add(trie * root, char * s, int id) {
  trie * p = root;
  for (; * s; s++) {
    if (!p->l[C2I(* s)]) p->l[C2I(* s)] = trie_new();
    p = p->l[C2I(* s)];
  }
  if (p->id == -1) p->id = id;
}

void
trie_build(trie * root) {
  trie * ary[100000], ** beg = ary, ** end = ary;
  for (* end ++ = root; beg < end; ) {
    trie * p = * beg ++;
    int i, len = LENOF(p->l);
    for (i = 0; i < len; i++) if (p->l[i]) {
      trie * s = p->suffix;
      while (s && !s->l[i]) s = s->suffix;
      s = p->l[i]->suffix = s ? s->l[i] : root;
      p->l[i]->dsuffix = s->id == -1 ? s->dsuffix : s;
      * end ++ = p->l[i];
    }
  }
}

void
trie_test(work * w, trie * root, char * s) {
  trie * p = root, * t;
  for (; * s; s++) {
    while (p && !p->l[C2I(* s)]) p = p->suffix;
    p = p ? p->l[C2I(* s)] : root;
    for (t = p; t; t = t->dsuffix)
      if (t->id != -1) w->occur[t->id]++;
  }
}

int
main(void) {
  work * w = work_new();
  trie * root = trie_new();
  int i, len, _;
  _=scanf("%d", &len);
  for (i = 0; i < len; i++) {
    _=scanf("%99s", i[w->p]);
    trie_add(root, i[w->p], i);
  }
  _=scanf("%99s", w->t);
  trie_build(root);
  trie_test(w, root, w->t);
  trie_del(root);
  for (i = 0; i < LENOF(w->occur); i++)
    if (w->occur[i] >= 0)
      printf("pattern %d  times %d\n", i, w->occur[i] + 1);
  work_del(w);
  return 0;
}
