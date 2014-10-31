#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

typedef struct {
  int x;
  int y;
} subm_t;

subm_t *
create_subms(int len) {
  return calloc(len, sizeof(subm_t));
}

void
print_points(subm_t * subms, int subms_len) {
  static char table[500 * 500];
  memset(table, '-', sizeof(table));
  int width = 11;
  int i = 0;
  for (; i < subms_len; i++) {
    table[subms[i].y * width + subms[i].x] = '+';
  }
  int row = 0;
  for (; row < width; row++) {
    int col = 0;
    for (; col < width; col++) {
      printf("%c", table[row * width + col]);
    }
    puts("");
  }
  puts("");
}

int
main(void) {
  int subms_len, origin_y;
  while (1) {
    scanf("%d%d", &subms_len, &origin_y);
    if (subms_len == 0 &&
        origin_y == 0) break;
    int i = 0;
    subm_t * subms = create_subms(subms_len);
    for (; i < subms_len; i++) {
      scanf("%d%d", &subms[i].x, &subms[i].y);
      if (subms[i].y > origin_y) {
        i--;
        subms_len--;
      }
    }
    print_points(subms, subms_len);
    free(subms);
  }
  return 0;
}
