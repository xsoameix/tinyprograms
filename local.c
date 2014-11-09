typedef struct {
  int * vals;
  int len;
} foo_t;

typedef enum {
  ZERO,
  ONE,
  TWO,
  THREE
} bar_t;

int
main(void) {
  foo_t a[THREE] = {
    {(int[]) {1, 0, 0}, 2},
    {(int[]) {2, 0, 0}, 2},
    {(int[]) {3, 0, 0}, 2}
  };
  return 0;
}
