#include <stdio.h>
#include <stddef.h>

// input file:
//  tabe %:r-input
//
// Compile command:
//  :Compile

void
swap(int * a, int * b) {
  int tmp = * a;
  * a = * b;
  * b = tmp;
}

void
print_ary(int * ary, size_t len) {
  size_t i = 0;
  for (; i < len; i++) {
    printf("%d ", ary[i]);
  }
  printf("\n");
}

size_t
partition(int * ary, size_t len, size_t pivot_i) {
  size_t i = 0;
  size_t small_len = 0;
  int pivot = ary[pivot_i];
  swap(&ary[pivot_i], &ary[len - 1]);
  for (; i < len; i++) {
    if (ary[i] < pivot) {
      swap(&ary[i], &ary[small_len]);
      small_len++;
    }
  }
  swap(&ary[len - 1], &ary[small_len]);
  return small_len;
}

void
quick_sort(int * ary, size_t len) {
  if (len == 0 || len == 1) return;
  size_t small_len = partition(ary, len, 0);
  quick_sort(ary, small_len);
  quick_sort(&ary[small_len + 1], len - small_len - 1);
}

int
main(void) {
  int ary[] = {2,4,2,5,3,5,3,1,7,6};
  size_t len = sizeof(ary) / sizeof(ary[0]);
  quick_sort(ary, len);
  print_ary(ary, len);
  return 0;
}
