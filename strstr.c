#include <stdio.h>
#include <string.h>

int
main(void) {
  char key[] = "foo";
  static const char map[] = "\1.foo\2.bar\3hey";
  char buf[sizeof(map)] = {0}, * p;
  snprintf(buf, sizeof(buf), ".%s", key);
  printf("buf: [%s]\n", buf);
  p = strstr(map, buf);
  if (p)
    printf("index: [%d]\n", p[-1]);
  return 0;
}
