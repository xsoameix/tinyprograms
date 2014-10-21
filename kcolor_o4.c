#include <stdio.h>
#include <string.h>

int matrix[20][20] = {0};
int player_matrix[20][20] = {0};

void
init_matrices(int size, int player_i) {
  memset(player_matrix, -1, sizeof(player_matrix));
  int i = 0;
  for (; i <= size; i++) {
    player_matrix[i][0] = player_matrix[0][i] = 0;
  }
  i = 1;
  for (; i <= size; i++) {
    int j = 1;
    for (; j <= size; j++) {
      if (matrix[i][j] == player_i) {
        player_matrix[i][j] = 1;
      }
    }
  }
  i = 1;
  for (; i <= size; i++) {
    int j = 1;
    for (; j <= size; j++) {
      player_matrix[i][j] += player_matrix[i][j-1] + player_matrix[i-1][j];
      player_matrix[i][j] -= player_matrix[i-1][j-1];
    }
  }
}

int
player_max_sum(int size, int players_len) {
  init_matrices(size, players_len);
  int max_sum = 0;
  int right = 0;
  for (; right <= size; right++) {
    int left = 0;
    for (; left <= right; left++) {
      int bottom = 0;
      for (; bottom <= size; bottom++) {
        int top = 0;
        for (; top <= bottom; top++) {
          int sum = (player_matrix[right][bottom] + player_matrix[left][top] -
                     player_matrix[right][top] - player_matrix[left][bottom]);
          if (sum > max_sum) {
            max_sum = sum;
          }
        }
      }
    }
  }
  return max_sum;
}

int
main(void) {
  int size, players_len;
  while (scanf("%d%d", &size, &players_len) == 2) {
    int i = 1;
    for (; i <= size; i++) {
      int j = 1;
      for (; j <= size; j++) {
        scanf("%d", &matrix[i][j]);
      }
    }
    int player_i = 1;
    for (; player_i <= players_len; player_i++) {
      printf("%d->%d\n", player_i, player_max_sum(size, player_i));
    }
    puts("");
  }
  return 0;
}
