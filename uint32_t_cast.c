#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int
main(void) {
  uint8_t small = 0xC2;
  uint8_t * ptr = &small;
  uint32_t big = * ptr;
  printf("%" PRIu32 "\n", big);
  return 0;
}
