#include <stdio.h>
#include <string.h>

void
rev(char * s) {
  char * e = s + strlen(s) - 1;
  while (s < e) * s ^= * e ^= * s ^= * e, s++, e--;
}

int
main(void) {
  char s[] = "abcd";
  rev(s);
  puts(s);
  return 0;
}
