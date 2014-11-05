#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int row;
  int col;
  int * cols;
} tab_t;

tab_t *
table_new(int row, int col) {
  size_t table_size = sizeof(tab_t);
  size_t cols_size = row * col * sizeof(int);
  tab_t * table = calloc(1, table_size + cols_size);
  table->row = row;
  table->col = col;
  table->cols = (void *) table + table_size;
  return table;
}

int
table_col(tab_t * table, int row, int col) {
  if (row >= table->row ||
      col >= table->col) return -1;
  return table->cols[row * table->row + col];
}

void
table_set_col(tab_t * table, int row, int col, int value) {
  if (row >= table->row ||
      col >= table->col) return;
  table->cols[row * table->row + col] = value;
}

void
table_print(tab_t * table) {
  int row = 0;
  for (; row < table->row; row++) {
    int col = 0;
    for (; col < table->col; col++) {
      printf("%5d", table_col(table, row, col));
    }
    puts("");
  }
}

int
main(void) {
  tab_t * table = table_new(3, 4);
  table_set_col(table, 0, 0, 100);
  table_set_col(table, 1, 1, 200);
  table_set_col(table, 2, 2, 300);
  table_set_col(table, 3, 3, 400);
  table_set_col(table, 4, 4, 500);
  int col = table_col(table, 3, 3);
  printf("table[2, 3] == %d\n", col);
  table_print(table);
  free(table);

  // table := Table new(3, 4)
  // table [2, 3] = 100
  // table [2, 4] = 100
  // col := table [2, 3]
  // puts("table[2, 3] == #col")
  // table print
  // free(table)
  return 0;
}
