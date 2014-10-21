#include <stdio.h>
#include <stdlib.h>

void
print_ary(int * ary, int len) {
  int i = 0;
  for (; i < len; i++) {
    printf("%d ", ary[i]);
  }
  printf("\n");
}

void
merge_ary(int * left, int left_len, int * right, int right_len) {
  int * sorted = calloc(left_len + right_len, sizeof(int));
  int left_i = 0;
  int right_i = 0;
  int i = 0;
  while (left_i < left_len && right_i < right_len) {
    sorted[i++] = (left[left_i] < right[right_i] ?
                   left[left_i++] : right[right_i++]);
  }
  while (left_i < left_len) {
    sorted[i++] = left[left_i++];
  }
  while (right_i < right_len) {
    sorted[i++] = right[right_i++];
  }
  left_i = 0;
  right_i = 0;
  i = 0;
  while (left_i < left_len) {
    left[left_i++] = sorted[i++];
  }
  while (right_i < right_len) {
    right[right_i++] = sorted[i++];
  }
  free(sorted);
}

void
merge_sort(int * ary, int len) {
  if (len <= 1) return;
  int mid = len / 2;
  merge_sort(ary, mid);
  merge_sort(&ary[mid], len - mid);
  merge_ary(ary, mid, &ary[mid], len - mid);
}

int *
create_ary(int len) {
  return calloc(len, sizeof(int));
}

int
main(void) {
  int len;
  scanf("%d", &len);
  int * ary = create_ary(len);
  int i = 0;
  for (; i < len; i++) {
    scanf("%d", &ary[i]);
  }
  print_ary(ary, len);
  merge_sort(ary, len);
  print_ary(ary, len);
  return 0;
}
