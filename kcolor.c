#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
get_max(int a, int b) {
  return a > b ? a : b;
}

int
ary_max_sum_kadane(int * ary, int len) {
  int max_sum = ary[0];
  int sum = max_sum;
  int i = 1;
  for (; i < len; i++) {
    sum = get_max(sum + ary[i], ary[i]);
    max_sum = get_max(sum, max_sum);
  }
  return max_sum;
}

void
init_player_matrix(int player, int * player_matrix, int * matrix, int size) {
  int i = 0;
  for (; i < size; i++) {
    int j = 0;
    for (; j < size; j++) {
      int col = i * size + j;
      player_matrix[col] = (matrix[col] == player) ? 1 : -1;
    }
  }
}

void
reset_max_sum_rows(int * max_sum_rows, int size) {
  int row_i = 0;
  for (; row_i < size; row_i++) {
    max_sum_rows[row_i] = 0;
  }
}

void
merge_sum_rows(int col_i, int * player_matrix, int * max_sum_rows, int size) {
  int row_i = 0;
  for (; row_i < size; row_i++) {
    int col = row_i * size + col_i;
    max_sum_rows[row_i] += player_matrix[col];
  }
}

int
player_max_sum(int player, int * matrix, int * player_matrix,
               int * max_sum_rows, int size) {
  init_player_matrix(player, player_matrix, matrix, size);
  int max_sum = -1;
  int left = 0;
  for (; left < size; left++) {
    int right = left;
    for (; right < size; right++) {
      merge_sum_rows(right, player_matrix, max_sum_rows, size);
      int sum = ary_max_sum_kadane(max_sum_rows, size);
      if (sum > max_sum) {
        max_sum = sum;
      }
    }
    reset_max_sum_rows(max_sum_rows, size);
  }
  return max_sum;
}

void
print_players(int players_len, int * matrix, int * player_matrix,
              int * max_sum_rows, int size) {
  int i = 0;
  for (; i < players_len; i++) {
    int player = i + 1;
    int sum = player_max_sum(player, matrix, player_matrix, max_sum_rows, size);
    printf("%d->%d\n", player, sum);
  }
  puts("");
}

void
create_matrix(int size, int ** matrix, int ** player_matrix,
              int ** max_sum_rows) {
  size = 20;
  int matrix_size = size * size * sizeof(int);
  int rows_size = size * sizeof(int);
  * matrix = calloc(1, matrix_size * 2 + rows_size);
  * player_matrix = * matrix + matrix_size;
  * max_sum_rows = * player_matrix + matrix_size;
  //static int matrix_storage[20][20];
  //static int player_matrix_storage[20][20];
  //static int rows_storage[20];
  //* matrix = * matrix_storage;
  //* player_matrix = * player_matrix_storage;
  //* max_sum_rows = rows_storage;
  //memset(matrix_storage, 0, sizeof(matrix_storage));
  //memset(player_matrix_storage, 0, sizeof(player_matrix_storage));
  //memset(rows_storage, 0, sizeof(rows_storage));
}

void
scan_matrix(int * matrix, int size) {
  int i = 0;
  for (; i < size; i++) {
    int j = 0;
    for (; j < size; j++) {
      scanf("%d", &matrix[i * size + j]);
    }
  }
}

int
main(void) {
  int size, players_len;
  while (scanf("%d%d\n", &size, &players_len) == 2) {
    int * matrix;
    int * player_matrix;
    int * max_sum_rows;
    create_matrix(size, &matrix, &player_matrix, &max_sum_rows);
    scan_matrix(matrix, size);
    print_players(players_len, matrix, player_matrix, max_sum_rows, size);
    free(matrix);
  }
  return 0;
}
