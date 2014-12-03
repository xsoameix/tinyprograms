#include <stdio.h>
#include <stdint.h>
#include <stdalign.h>

typedef struct {
  uint16_t txn;  // transaction id
  uint16_t prot; // protocol
  uint16_t len;
  uint8_t unit;
  uint8_t op;
  uint8_t panel;
  uint8_t addr;
  uint16_t data;
} mtcp_t; // modbus tcp

int
main(void) {
  printf("sizeof %zu\n", sizeof(mtcp_t));
  printf("alignof %zu\n", alignof(mtcp_t));
  return 0;
}
