#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x;
  int y;
  int rank;
} point_t;

int
cmp_points_in_y(const void * a, const void * b) {
  const point_t * point_a = a;
  const point_t * point_b = b;
  return point_a->y - point_b->y;
}

void
sort_points_in_y(point_t * points, int len) {
  qsort(points, len, sizeof(point_t), cmp_points_in_y);
}

point_t *
create_points(int len) {
  return calloc(len, sizeof(point_t));
}

point_t *
clone_points(point_t * points, int len) {
  point_t * clone = create_points(len);
  int i = 0;
  for (; i < len; i++) {
    clone[i] = points[i];
  }
  return clone;
}

void
merge_points(point_t * points, int len) {
  int mid = len / 2;
  sort_points_in_y(points, mid);
  sort_points_in_y(&points[mid], len - mid);
  int left = 0;
  int right = mid;
  int rank = 0;
  while (left < mid && right < len) {
    if (points[left].y < points[right].y) {
      rank++;
      left++;
    } else {
      points[right].rank += rank;
      right++;
    }
  }
  while (right < len) {
    points[right].rank += rank;
    right++;
  }
}

void
print_ary(point_t * ary, int len) {
  int i = 0;
  for (; i < len; i++) {
    printf("[%d %d %d]", ary[i].x, ary[i].y, ary[i].rank);
    if (i != len - 1) {
      printf(" ");
    }
  }
  puts("");
}

void
rank_points(point_t * points, int len) {
  if (len == 1) return;
  int mid = len / 2;
  rank_points(points, mid);
  rank_points(&points[mid], len - mid);
  merge_points(points, len);
  print_ary(points, len);
}

int
cmp_points_in_x(const void * a, const void * b) {
  const point_t * point_a = a;
  const point_t * point_b = b;
  return point_a->x - point_b->x;
}

void
sort_points_in_x(point_t * points, int len) {
  qsort(points, len, sizeof(point_t), cmp_points_in_x);
}

int
main(void) {
  int len;
  scanf("%d", &len);
  point_t * points = create_points(len);
  int i = 0;
  for (; i < len; i++) {
    scanf("%d%d", &points[i].x, &points[i].y);
  }
  sort_points_in_x(points, len);
  rank_points(points, len);
  return 0;
}
