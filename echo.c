#include <stdio.h>

int
main(int len, char ** args) {
  int i = 1;
  for (; i < len; i++) {
    printf("%s", args[i]);
    if (i != len - 1) {
      printf(" ");
    }
  }
  if (len > 1) {
    puts("");
  }
  return 0;
}
