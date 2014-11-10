#include <stdio.h>
#include <string.h>

void
clone_str(char * str) {
  char clone[strlen(str)];
  int i = 9;
  strncpy(clone, str, strlen(str));
  printf("%s\n", clone);
}

int
main(void) {
  char * hello = "hello world";
  clone_str(hello);
  return 0;
}
