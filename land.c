#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef long long num_t;

typedef struct {
  num_t rows;
  num_t cols;
} mat_t;

num_t
get_max(num_t a, num_t b) {
  return a > b ? a : b;
}

num_t
ary_max_sum_kadane(num_t * ary, num_t len,
                   num_t * max_begin, num_t * max_end) {
  num_t max_sum = ary[0];
  num_t sum = max_sum;
  num_t begin = 0;
  * max_begin, * max_end = 0;
  num_t i = 1;
  for (; i < len; i++) {
    if (sum < 0) {
      begin = i;
    }
    sum = get_max(sum + ary[i], ary[i]);
    if (sum > max_sum) {
      * max_begin = begin;
      * max_end = i;
    }
    max_sum = get_max(sum, max_sum);
  }
  return max_sum;
}

void
init_player_matrix(num_t * player_matrix, num_t * matrix, mat_t size) {
  num_t i = 0;
  for (; i < size.rows; i++) {
    num_t j = 0;
    for (; j < size.cols; j++) {
      num_t col = i * size.cols + j;
      player_matrix[col] = (matrix[col] <= 3) ? matrix[col] : LLONG_MIN / 10000;
    }
  }
}

void
reset_max_sum_rows(num_t * max_sum_rows, mat_t size) {
  num_t row_i = 0;
  for (; row_i < size.rows; row_i++) {
    max_sum_rows[row_i] = 0;
  }
}

void
merge_sum_rows(num_t col_i, num_t * player_matrix, num_t * max_sum_rows,
               mat_t size) {
  num_t row_i = 0;
  for (; row_i < size.rows; row_i++) {
    num_t col = row_i * size.cols + col_i;
    max_sum_rows[row_i] += player_matrix[col];
  }
}

num_t
player_max_sum(num_t * matrix, num_t * player_matrix,
               num_t * max_sum_rows,
               num_t * max_top, num_t * max_bottom,
               num_t * max_left, num_t * max_right,
               mat_t size) {
  init_player_matrix(player_matrix, matrix, size);
  num_t max_sum = -1;
  num_t left = 0;
  for (; left < size.cols; left++) {
    num_t right = left;
    for (; right < size.cols; right++) {
      merge_sum_rows(right, player_matrix, max_sum_rows, size);
      num_t top, bottom;
      num_t sum = ary_max_sum_kadane(max_sum_rows, size.rows, &top, &bottom);
      if (sum > max_sum) {
        max_sum = sum;
        * max_top = top;
        * max_bottom = bottom;
        * max_left = left;
        * max_right = right;
      }
    }
    reset_max_sum_rows(max_sum_rows, size);
  }
  return max_sum;
}

void
print_players(num_t * matrix, num_t * player_matrix,
              num_t * max_sum_rows, mat_t size) {
  num_t top, bottom, left, right;
  num_t sum = player_max_sum(matrix, player_matrix, max_sum_rows,
                             &top, &bottom, &left, &right, size);
  printf("%lld %lld %lld %lld %lld\n", sum, left, top, right, bottom);
}

#define LEN 110

void
create_matrix(mat_t size, num_t ** matrix, num_t ** player_matrix,
              num_t ** max_sum_rows) {
  //size = 20;
  //num_t matrix_size = size * size * sizeof(num_t);
  //num_t rows_size = size * sizeof(num_t);
  //* matrix = calloc(1, matrix_size * 2 + rows_size);
  //* player_matrix = * matrix + matrix_size;
  //* max_sum_rows = * player_matrix + matrix_size;
  static num_t matrix_storage[LEN][LEN];
  static num_t player_matrix_storage[LEN][LEN];
  static num_t rows_storage[LEN];
  * matrix = * matrix_storage;
  * player_matrix = * player_matrix_storage;
  * max_sum_rows = rows_storage;
  memset(matrix_storage, 0, sizeof(matrix_storage));
  memset(player_matrix_storage, 0, sizeof(player_matrix_storage));
  memset(rows_storage, 0, sizeof(rows_storage));
}

void
scan_matrix(num_t * matrix, mat_t size) {
  num_t i = 0;
  for (; i < size.rows; i++) {
    num_t j = 0;
    for (; j < size.cols; j++) {
      scanf("%lld", &matrix[i * size.cols + j]);
    }
  }
}

num_t
main(void) {
  mat_t size = {0};
  while (1) {
    scanf("%lld%lld", &size.rows, &size.cols);
    if (!size.rows && !size.cols) break;
    num_t * matrix;
    num_t * player_matrix;
    num_t * max_sum_rows;
    create_matrix(size, &matrix, &player_matrix, &max_sum_rows);
    scan_matrix(matrix, size);
    print_players(matrix, player_matrix, max_sum_rows, size);
    //free(matrix);
  }
  return 0;
}
