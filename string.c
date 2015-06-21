#include <stdio.h>

int
main(int argc, char ** argv) {
  while (--argc || !putchar('\n')) putchar((++argv)[0][0]);
  return 0;
}
