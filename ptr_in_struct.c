typedef struct {
  int len;
  int * numbers;
} nums_t;

nums_t foo = {2, (int[]){1, 2}};

int
main(void) {
  return 0;
}
