#include <stdint.h>

#define RATE 9600 // bits per second
#define BITS_PER_BYTE 8
#define NANOSECOND (1000 * 1000 * 1000)
#define MAX_BYTES_PER_ROUND (12 * 2) // send and recv = 1 round
#define SLEEP_TIME /* nanosecond per round */ \
  (uint64_t) MAX_BYTES_PER_ROUND * BITS_PER_BYTE * NANOSECOND / RATE

int
main(void) {
  int a = SLEEP_TIME;
  return 0;
}
