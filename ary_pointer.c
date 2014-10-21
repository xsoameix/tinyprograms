#include <stdio.h>
#include <stdint.h>

int
main(void) {
  short * i = (short[]) {0,1,2,3,4,5,6,7,8,9,
                         10,11,12,13,14,15,16,17,18,19};
  short ary = 0;
  short len = 4;
  for (; ary < len; ary++) {
    // 0 3 6 9
    printf("%hd ", ary[(short *) &ary[(int *) i]]);
  }
  puts("");
  ary = 0;
  for (; ary < len; ary++) {
    // 0 4 8 12
    printf("%hd ", ary[&ary[(int *) i]]);
  }
  puts("");
  ary = 0;
  for (; ary < len; ary++) {
    // 0 5 10 15
    printf("%hd ", ary[(short *) &ary[&ary[(int *) i]]]);
  }
  puts("");
  ary = 0;
  for (; ary < len; ary++) {
    // 0 6 12 18
    printf("%hd ", ary[&ary[&ary[(int *) i]]]);
  }
  puts("");
  return 0;
}
