#include <stdio.h>
#include <limits.h>

#define LEN 5

int w[LEN][LEN] = {
  {-1,  3,  8, -1,  4},
  {-1, -1, -1,  1,  7},
  {-1,  4, -1, -1, -1},
  { 2, -1,  5, -1, -1},
  {-1, -1, -1,  6, -1}
};
int d[LEN][LEN];
int p[LEN][LEN];

void
matrix_print(int show_d, int show_p) {
  if (show_d) {
    for (int i=0; i<LEN; i++) {
      for (int j=0; j<LEN; j++)
        if (d[i][j] == INT_MAX / 2) {
          printf(" x ");
        } else {
          printf("%2d ", d[i][j]);
        }
      puts("");
    }
    puts("");
  }
  if (show_p) {
    for (int i=0; i<LEN; i++) {
      for (int j=0; j<LEN; j++)
        if (p[i][j] == -1) {
          printf(" x ");
        } else {
          printf("%2d ", p[i][j]);
        }
      puts("");
    }
  }
  puts("");
}

void
floyd_warshall(void) {
  for (int i=0; i<LEN; i++)
    for (int j=0; j<LEN; j++) {
      d[i][j] = INT_MAX / 2;
      p[i][j] = -1;
    }

  for (int i=0; i<LEN; i++)
    for (int j=0; j<LEN; j++)
      if (w[i][j] > 0) {
        d[i][j] = w[i][j];
        p[i][j] = i;
      }

  for (int i=0; i<LEN; i++) {
    d[i][i] = 0;
    p[i][i] = -1;
  }

  matrix_print(1, 1);

  for (int k=0; k<LEN; k++) {
    printf("k == %d\n", k);
    for (int i=0; i<LEN; i++)
      for (int j=0; j<LEN; j++)
        if (d[i][k] + d[k][j] < d[i][j]) {
          d[i][j] = d[i][k] + d[k][j];
          p[i][j] = p[k][j];
        }
    matrix_print(0, 1);
  }
  matrix_print(1, 1);
}

int
main(void) {
  floyd_warshall();
  return 0;
}
