#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef int kth_t;

int indent = 0;

void
print_ary(kth_t * ary, size_t len) {
  size_t indent_i = 0;
  for (; indent_i < indent; indent_i++) {
    printf(" ");
  }
  size_t i = 0;
  for (; i < len; i++) {
    printf("%d ", ary[i]);
  }
  printf("\n");
}

void
swap(kth_t * a, kth_t * b) {
  kth_t tmp = * a;
  * a = * b;
  * b = tmp;
}

size_t
partition(kth_t * ary, size_t len, size_t pivot_i) {
  size_t i = 0;
  size_t small_len = 0;
  kth_t pivot = ary[pivot_i];
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

size_t selection_algorithm(kth_t * ary, size_t len, size_t kth_smallest_num);

size_t
median_of_medians(kth_t * ary, size_t len) {
  size_t medians_len = (len + 4) / 5;
  size_t i = 0;
  for (; i < medians_len; i++) {
    size_t left = i * 5;
    size_t right = left + 4;
    if (right >= len) right = len - 1;
    size_t median_i = selection_algorithm(
        &ary[left], right - left + 1, (right - left) / 2);
    swap(&ary[i], &ary[left + median_i]);
  }
  return selection_algorithm(ary, medians_len, medians_len / 2);
}

int
compare_num(const void * a, const void * b) {
  const kth_t * num_a = a;
  const kth_t * num_b = b;
  return * num_a - * num_b;
}

size_t
selection_algorithm(kth_t * ary, size_t len, size_t kth_smallest_num) {
  if (len <= 5) {
    qsort(ary, len, sizeof(kth_t), compare_num);
    return kth_smallest_num;
  }
  size_t pivot_i = median_of_medians(ary, len);
  size_t small_len = partition(ary, len, pivot_i);
  if (kth_smallest_num == small_len) return small_len;
  if (kth_smallest_num < small_len) {
    return selection_algorithm(ary, small_len, kth_smallest_num);
  } else {
    return (small_len + 1 + selection_algorithm(
            &ary[small_len + 1],
            len - small_len - 1,
            kth_smallest_num - small_len - 1));
  }
}

kth_t *
create_ary(size_t len) {
  return calloc(len, sizeof(kth_t));
}

kth_t
main(void) {
  size_t len, kth_smallest_num;
  scanf("%zu%zu", &len, &kth_smallest_num);
  kth_t * ary = create_ary(len);
  size_t i = 0;
  for (; i < len; i++) {
    scanf("%d", &ary[i]);
  }
  size_t kth_smallest_num_i = selection_algorithm(ary, len, kth_smallest_num);
  printf("%d\n", ary[kth_smallest_num_i]);
  print_ary(ary, len);
  return 0;
}
