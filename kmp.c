#include <stdio.h>
#include <string.h>

void
set_ft(int * ft, char * p) {
  int i, f = ft[0] = -1, len = strlen(p);
  for (i = 1; i < len; i[ft] = f, i++) {
    while (f >= 0 && p[f + 1] != p[i]) f = f[ft];
    if (p[f + 1] == p[i]) f++;
  }
}

void
print_ft(int * ft, char * p) {
  printf("prefix | border\n");
  int i, j, len = strlen(p);
  for (i = 0; i < len; i++) {
    for (j = 0; j < i + 1; j++) putchar(j[p]);
    for (j = 0; j < 8 - i; j++) putchar(' ');
    for (j = 0; j < ft[i] + 1; j++) putchar(j[p]);
    for (j = 0; j < 8 - ft[i]; j++) putchar(' ');
    putchar('\n');
  }
}

void
mp(int * ft, char * t, char * p) {
  int i, f, plen = strlen(p), tlen = strlen(t);
  if (plen > tlen) return;
  for (i = 0, f = -1; i < tlen; i++) {
    while (f >= 0 && p[f + 1] != t[i]) f = f[ft];
    if (p[f + 1] == t[i]) f++;
    if (f == plen - 1) printf("%d\n", i + 1 - plen);
  }
}

int
main(void) {
  char p[] = "abzabc";
  int ft[sizeof(p)]; /* fail table */
  set_ft(ft, p);
  print_ft(ft, p);
  mp(ft, "abzabc", p);
  return 0;
}
