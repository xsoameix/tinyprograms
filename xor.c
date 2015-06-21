#include <stdio.h>

int
main(void) {
  long long a[] = {1,2,3}, b[] = {3,4,5}, c[] = {5, 6, 7}, i = 0, l = 1;
  a[i] ^= b[i] ^= c[i++]; /* $ gcc % -Wsequence-point -o %.bin */
  printf("%lld %lld %lld, %lld %lld %lld, %lld %lld %lld\n",
         a[0], a[1], a[2], b[0], b[1], b[2], c[0], c[1], c[2]);
  /* 123456 */
  /* 173656 */
  /* 103156 */
  /* 133256 */
  /* 133156 */
  /* 133 315 567 */
  printf("%d\n", 2 ^ 1);
  a[i++] = b[i++];
  return 0;
}
