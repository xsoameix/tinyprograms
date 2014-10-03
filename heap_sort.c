#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// input file:
//  tabe %:r-input
//
// Compile command:
//  :Compile

void
print_ary(int * ary, int len) {
  int i = 0;
  for (; i < len; i++) {
    printf("%d", ary[i]);
    if (i != len - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

void
reverse_print_ary(int * ary, int len) {
  int i = 0;
  for (; i < len; i++) {
    printf("%d", ary[len - i - 1]);
    if (i != len - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

void
swap(int * a, int * b) {
  int tmp = * a;
  * a = * b;
  * b = tmp;
}

void
shift_down(int * ary, int start, int end) {
  int root = start;
  while (root * 2 + 1 <= end) {
    int child = root * 2 + 1;
    int to_swap = root;
    if (ary[to_swap] < ary[child]) {
      to_swap = child;
    }
    if (child + 1 <= end &&
        ary[to_swap] < ary[child + 1]) {
      to_swap = child + 1;
    }
    if (to_swap != root) {
      print_ary(ary, end + 1);
      swap(&ary[root], &ary[to_swap]);
      root = to_swap;
    } else {
      return;
    }
  }
}

void
heapify(int * ary, int len) {
  int start = ((int) len - 2) / 2;
  while (start >= 0) {
    shift_down(ary, start, len - 1);
    start--;
  }
}

void
heap_sort(int * ary, int len) {
  //heapify(ary, len);
  int end = len - 1;
  while (end > 0) {
    print_ary(ary, end + 1);
    swap(&ary[end], &ary[0]);
    print_ary(ary, end + 1);
    end--;
    shift_down(ary, 0, end);
  }
  print_ary(ary, end + 1);
}

int *
create_ary(int len) {
  return malloc(len * sizeof(int));
}

int
main(void) {
  int arys_i = 0;
  int arys_len;
  scanf("%d\n", &arys_len);
  for (; arys_i < arys_len; arys_i++) {
    int i = 0;
    int len;
    scanf("%d\n", &len);
    int * ary = create_ary(len);
    for (; i < len; i++) {
      scanf("%d", &ary[i]);
      if (i != len - 1) {
        scanf(",");
      }
    }
    scanf("\n");
    i = 0;
    for (; i < len; i++) {
      heapify(ary, i + 1);
      print_ary(ary, i + 1);
    }
    heap_sort(ary, len);
    reverse_print_ary(ary, len);
    free(ary);
    puts("*");
  }
  return 0;
}
