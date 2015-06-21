#include <stdio.h>
#include <string.h>

int
f(char l, char r) {
  static char op[] = "(i+-*/^)", t[sizeof(op)][sizeof(op)] = {
    /*       (  i  +  -  *  /  ^  )  # */
    /* ( */ {1, 1, 1, 1, 1, 1, 1, 2, 0},
    /* i */ {1, 1, 0, 0, 0, 0, 0, 0, 0},
    /* + */ {1, 1, 0, 0, 1, 1, 1, 0, 0},
    /* - */ {1, 1, 0, 0, 1, 1, 1, 0, 0},
    /* * */ {1, 1, 0, 0, 0, 0, 1, 0, 0},
    /* / */ {1, 1, 0, 0, 0, 0, 1, 0, 0},
    /* ^ */ {1, 1, 0, 0, 0, 0, 0, 0, 0},
    /* ) */ {1, 1, 0, 0, 0, 0, 0, 0, 0},
    /* # */ {1, 1, 1, 1, 1, 1, 1, 1, 2}};
  char i = t[strchr(op, l)-op][strchr(op, r)-op];
  printf("%c %c %c\n", (l ? l : '#'), (i == 1 ? '<' : i == 0 ? '>' : '='), (r ? r : '#'));
  return t[strchr(op, l)-op][strchr(op, r)-op];
}

int
v(char * s, int i) {
  return i - (strchr("(i+-*/^)", s[i-1]) > 0 ? 1 : 2);
}

int
main(void) {
  char s[100] = {0}, t[] = "(i+i)*i";
  int i, p, si = 1, ti = 0, tl = sizeof(t) / sizeof(t[0]), e = 2;
  for (; ti < tl; e == 1 && (s[p+1] = 'N', si = p + 2, e = 2)) {
    if (e != 0 && f(s[i = v(s, si)], t[ti])) s[si++] = t[ti++];
    else if ((e = f(s[p = v(s, i)], s[i]) == 1) || (i = p));
    int k = 0;
    while (k < si) putchar(s[k] ? s[k] : '#'), k++;
    while (k < 10) putchar(' '), k++;
    printf("%d %d\n", i, si);
  }
  return 0;
}
