#include <stdio.h>
#include <stdlib.h>

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
      printf(" ");
    }
  }
  printf("\n");
}

#define BASE 10

void
radix_sort(int * ary, int len) {
  int buk[BASE][20] = {0};
  int buks_len[20] = {0};
  int base = 1;
  while (base <= 10000) {
    int i = 0;
    int changed = 0;
    for (; i < len; i++) {
      int lsd = (ary[i] / base) % BASE;
      buk[lsd][buks_len[lsd]++] = ary[i];
      if (lsd != 0) {
        changed = 1;
      }
    }
    i = 0;
    int buks_i = 0;
    for (; buks_i < BASE; buks_i++) {
      if (buks_len[buks_i] == 0) continue;
      int buk_i = 0;
      for (; buk_i < buks_len[buks_i]; buk_i++) {
        ary[i++] = buk[buks_i][buk_i];
      }
      buks_len[buks_i] = 0;
    }
    if (changed) {
      print_ary(ary, len);
      changed = 0;
    }
    base *= BASE;
  }
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
    radix_sort(ary, len);
    free(ary);
    puts("*");
  }
  return 0;
}
