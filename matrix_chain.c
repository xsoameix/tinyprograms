#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
  int len;
  int * vals; // len * int for rows of each matrix +
              // 1   * int for cols of last matrix
} matc_t; // matrix chain

typedef struct {
  int len;
  int * vals;
  int * mids;
} htab_t; // half table

int
htab_is_valid(htab_t * htab, int row, int col) {
  int len = htab->len;
  return (row < len &&
          col < len &&
          row <= col);
}

int *
htab_col_offset(htab_t * htab, int * vals, int row, int col) {
  if (!htab_is_valid(htab, row, col)) return NULL;
  int len = htab->len;
  int row_offset = (len * 2 + (row - 1) * -1) * row / 2;
  int col_offset = col - row;
  return &vals[row_offset + col_offset];
}

int
htab_col(htab_t * htab, int row, int col) {
  return * htab_col_offset(htab, htab->vals, row, col);
}

void
htab_set_col(htab_t * htab, int row, int col, int val) {
  * htab_col_offset(htab, htab->vals, row, col) = val;
}

int
htab_mid(htab_t * htab, int row, int col) {
  return * htab_col_offset(htab, htab->mids, row, col);
}

void
htab_set_mid(htab_t * htab, int row, int col, int mid) {
  * htab_col_offset(htab, htab->mids, row, col) = mid;
}

htab_t *
create_htab(matc_t * matc) {
  int len = matc->len;
  size_t htab_size = sizeof(htab_t);
  size_t vals_size = ((1 + len) * len / 2) * sizeof(int);
  htab_t * htab = calloc(1, htab_size + vals_size * 2);
  htab->len = len;
  htab->vals = (void *) htab + htab_size;
  htab->mids = (void *) htab->vals + vals_size;
  return htab;
}

htab_t *
min_matc_product(matc_t * matc) {
  htab_t * htab = create_htab(matc);
  int len = 1;
  for (; len <= matc->len; len++) {
    int start = 0;
    for (; start < matc->len - len + 1; start++) {
      int end = start + len - 1;
      if (start == end) {
        htab_set_col(htab, start, end, 0);
      } else {
        int min = INT_MAX;
        int mid = start;
        for (; mid < end; mid++) {
          int col = (htab_col(htab, start, mid) +
                     htab_col(htab, mid + 1, end) +
                     matc->vals[start] *
                     matc->vals[mid + 1] *
                     matc->vals[end + 1]);
          if (col < min) {
            min = col;
            htab_set_col(htab, start, end, col);
            htab_set_mid(htab, start, end, mid);
          }
        }
      }
    }
  }
  return htab;
}

void
print_htab(htab_t * htab) {
  int len = htab->len;
  int row = 0;
  for (; row < len; row++) {
    int col = row;
    for (; col < len; col++) {
      printf("%6d", htab_col(htab, row, col));
    }
    puts("");
  }
}

void
print_matc_traverse(htab_t * htab, int start, int end) {
  if (start == end) {
    printf("%d", start);
    return;
  }
  int mid = htab_mid(htab, start, end);
  printf("(");
  print_matc_traverse(htab, start, mid);
  print_matc_traverse(htab, mid + 1, end);
  printf(")");
}

void
print_min_matc_product(htab_t * htab) {
  print_matc_traverse(htab, 0, htab->len - 1);
  puts("");
}

matc_t *
create_matc(int len) {
  size_t matc_size = sizeof(matc_t);
  size_t vals_size = (len + 1) * sizeof(int);
  matc_t * matc = calloc(1, matc_size + vals_size);
  matc->len = len;
  matc->vals = (void *) matc + matc_size;
  return matc;
}

matc_t *
scan_matc(int len) {
  matc_t * matc = create_matc(len);
  int i = 0;
  for (; i < len; i++) {
    scanf("%d", &matc->vals[i]);
  }
  if (len > 1) {
    scanf("%d", &matc->vals[len]);
  }
  return matc;
}

int
main(void) {
  int len;
  while (scanf("%d", &len) == 1) {
    matc_t * matc = scan_matc(len);
    htab_t * htab = min_matc_product(matc);
    print_htab(htab);
    print_min_matc_product(htab);
    free(htab);
    free(matc);
  }
  return 0;
}
