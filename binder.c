#include <stdint.h>

typedef struct {
  size_t len;
  uint8_t * bytes;
} ins_t;

ins_t
create_call(void * from, void * to) {
  ins_t ins;
  ins.bytes = "\xE8\0\0\0\0";
  ins.len = 5;
  * (uint32_t *) &ins.bytes[1] = to - (from + 5);
  return ins;
}

int
sum(int a, int b) {
  return a + b;
}
