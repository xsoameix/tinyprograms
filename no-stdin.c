#include <stdio.h>

int
main(void) {
  char s[] = {
    #include "no-stdin.txt"
  };
  long long i = 0, l = sizeof(s), c[] = {1,2};
  printf("len %lld\n", l);
  while (s[l-i] ^= s[l-i] ^= s[l-i++-2], i < l / 2 - 1) {
    printf("i %lld\n", i);
  };
  printf("%02X ", s[0]);
  printf("%02X ", s[1]);
  printf("%02X ", s[2]);
  printf("%02X ", s[3]);
  printf("%02X ", s[4]);
  return 0;
}
