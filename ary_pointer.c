#include <stdio.h>
#include <stdint.h>

// 如何只用指標存取某個倍數 n 的元素？
// examples:
//   n == 3, => 0 3 6 9
//   n == 4, => 0 4 8 12
//   n == 5, => 0 5 10 15
//   n == 6, => 0 6 12 18

int
main(void) {
  short * i = (short[]) {0,1,2,3,4,5,6,7,8,9,
                         10,11,12,13,14,15,16,17,18,19};
  short ary = 0;
  short len = 4;
  for (; ary < len; ary++) {
    // 0 3 6 9
    printf("%hd ", ((short *) &ary[(int *) i])[ary]);
  }
  puts("");
  ary = 0;
  for (; ary < len; ary++) {
    // 0 4 8 12
    printf("%hd ", (&ary[(int *) i])[ary]);
  }
  puts("");
  ary = 0;
  for (; ary < len; ary++) {
    // 0 5 10 15
    printf("%hd ", ary[(short *) &(&ary[(int *) i])[ary]]);
  }
  puts("");
  ary = 0;
  for (; ary < len; ary++) {
    // 0 6 12 18
    printf("%hd ", ary[&(&ary[(int *) i])[ary]]);
  }
  puts("");
  printf("%hd\n", 0[i]);
  printf("%hd\n", 1[i]);
  printf("%hd\n", 2[i]);
  printf("%hd\n", 3[i]);
  return 0;
}
