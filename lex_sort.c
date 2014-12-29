#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100
#define STRS_LEN 101

int
cmp_str(const void * a, const void * b) {
  const char * str_a = a;
  const char * str_b = b;
  int i = 0;
  while (1) {
    char a = str_a[i];
    char b = str_b[i];
    if (a == '\0' && b == '\0') return 0;
    if (a == '\0') return -1;
    if (b == '\0') return 1;
    if (a != b) return a - b;
    i++;
  }
}

int
main(void) {
  int len;
  while (1) {
    scanf("%d", &len);
    if (len == 0) break;
    scanf("\n");
    static char strs[LEN][STRS_LEN];
    memset(strs, 0, sizeof(strs));
    int i = 0;
    for (; i < len; i++) {
      int str_i = 0;
      while (1) {
        char c;
        scanf("%c", &c);
        if (c == '\n') break;
        strs[i][str_i++] = c;
      }
    }
    qsort(strs, len, sizeof(strs[0]), cmp_str);
    i = 0;
    for (; i < len; i++) {
      printf("%s\n", strs[i]);
    }
    printf("*\n");
  }
  return 0;
}
