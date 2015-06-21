#include <stdio.h>
#include <stdint.h>
#include <stdalign.h>

typedef struct {
  uint16_t a;
  uint8_t b;
} normal_t;

typedef struct {
  uint16_t a;
  uint8_t b;
} packed_t;

int
main(void) {
  printf("alignof(normal_t) %zu\n", alignof(normal_t));
  printf("sizeof(normal_t) %zu\n", sizeof(normal_t));
  printf("alignof(packed_t) %zu\n", alignof(packed_t));
  printf("sizeof(packed_t) %zu\n", sizeof(packed_t));
  return 0;
}
