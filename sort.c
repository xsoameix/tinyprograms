#include <stdio.h>
#include <stdlib.h>

int
cmp(const void * a, const void * b) {
  return * (const char *) a - * (const char *) b;
}

int
main(void) {
  FILE * in = fopen("sort.txt", "r");
  int i = 0;
  static char buf[30][30];
  while (i < 30 && fgets(buf[i++], sizeof(buf[0]), in));
  qsort(buf, sizeof(buf) / sizeof(buf[0]), sizeof(buf[0]), cmp);
  i = 0;
  while (i < 30) printf("%s", buf[i++]);
  fclose(in);
  return 0;
}
