#include <stdio.h>
#include <string.h>

typedef long long num_t;

#define PATH_LEN 450

// empty, block, tried
enum {
  EMP,
  BLK,
  TRY
};

typedef struct {
  num_t row;
  num_t col;
  char dir; // direction
  num_t dir_i;
} cell_t;

num_t lim, rows, cols;
cell_t path[PATH_LEN];
num_t save[PATH_LEN];
num_t maze[PATH_LEN][PATH_LEN];

int
main(void) {
  while (1) {
    scanf("%lld", &lim);
    scanf("%lld", &cols);
    scanf("%lld", &rows);
    char c;
    scanf("%c", &c);
    //printf("lim cols roms %lld %lld %lld\n", lim, cols, rows);
    if (lim == 0 && cols == 0 && rows == 0) break;
    num_t i = 0;
    for (; i < rows; i++) {
      num_t next_line = 0;
      num_t j = 0;
      for (; j < cols; j++) {
        maze[i][j] = EMP;
      }
      j = 0;
      for (; j < cols; j++) {
        char c;
        scanf("%c", &c);
        //printf("[%c]", c);
        if (c == '#') maze[i][j] = BLK;
        if (c == '\n') {
          next_line = 1;
          break;
        }
      }
      //puts("");
      if (!next_line) scanf("%c", &c);
    }
    num_t path_len = 0;
    num_t save_len = 0;
    num_t save_i = 0;
    num_t row = 0;
    num_t col = 0;
    maze[row][col] = TRY;
    path[path_len++] = (cell_t) {row, col, '?', 1};
    while (1) {
      num_t pdir_i = path[path_len - 1].dir_i;
      //printf("%lld %lld dir %lld, len %lld\n", row, col, pdir_i, path_len);
      if (path_len < lim + 1 &&
          col > 0 && maze[row][col - 1] == EMP &&
          pdir_i == 0) {
        col -= 1;
        path[path_len - 1].dir_i = 1;
        path[path_len++] = (cell_t) {row, col, 'L', 0};
        maze[row][col] = TRY;
      } else if (path_len < lim + 1 &&
                 row > 0 && maze[row - 1][col] == EMP &&
                 pdir_i >= 0 && pdir_i <= 1) {
        row -= 1;
        path[path_len - 1].dir_i = 2;
        path[path_len++] = (cell_t) {row, col, 'U', 0};
        maze[row][col] = TRY;
      } else if (path_len < lim + 1 &&
                 row < rows - 1 && maze[row + 1][col] == EMP &&
                 pdir_i >= 0 && pdir_i <= 2) {
        row += 1;
        path[path_len - 1].dir_i = 3;
        path[path_len++] = (cell_t) {row, col, 'D', 0};
        maze[row][col] = TRY;
      } else if (path_len < lim + 1 &&
                 col < cols - 1 && maze[row][col + 1] == EMP &&
                 pdir_i >= 0 && pdir_i <= 3) {
        col += 1;
        path[path_len - 1].dir_i = 4;
        path[path_len++] = (cell_t) {row, col, 'R', 0};
        maze[row][col] = TRY;
      } else {
        if (row == rows - 1 && col == cols - 1) {
          num_t i = 1;
          for (; i < path_len; i++) {
            printf("%c", path[i].dir);
          }
          puts("");
        } else if (row == 0 && col == 0) {
          break;
        }
        maze[row][col] = EMP;
        path_len--;
        cell_t * cell = &path[path_len - 1];
        row = cell->row;
        col = cell->col;
        //printf("prev\n");
      }
    }
  }
  return 0;
}
