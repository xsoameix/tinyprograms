#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <float.h>
#include <math.h>

typedef struct point {
  double x;
  double y;
} point_t;

typedef struct pair {
  point_t a;
  point_t b;
  double mid; // The distance of this point and a is same as
              // the distance of this point and b.
              // This point is on y = c.
} pair_t;

typedef double kth_t;

void
print_ary(kth_t * ary, size_t len) {
  size_t i = 0;
  for (; i < len; i++) {
    printf("%lf ", ary[i]);
  }
  printf("\n");
}

void
swap(kth_t * a, kth_t * b) {
  kth_t tmp = * a;
  * a = * b;
  * b = tmp;
}

size_t
partition(kth_t * ary, size_t len, size_t pivot_i) {
  size_t i = 0;
  size_t small_len = 0;
  kth_t pivot = ary[pivot_i];
  swap(&ary[pivot_i], &ary[len - 1]);
  for (; i < len; i++) {
    if (ary[i] < pivot) {
      swap(&ary[i], &ary[small_len]);
      small_len++;
    }
  }
  swap(&ary[len - 1], &ary[small_len]);
  return small_len;
}

size_t selection_algorithm(kth_t * ary, size_t len, size_t kth_smallest_num);

size_t
median_of_medians(kth_t * ary, size_t len) {
  size_t medians_len = (len + 4) / 5;
  size_t i = 0;
  for (; i < medians_len; i++) {
    size_t left = i * 5;
    size_t right = left + 4;
    if (right >= len) right = len - 1;
    size_t median_i = selection_algorithm(
        &ary[left], right - left + 1, (right - left) / 2);
    swap(&ary[i], &ary[left + median_i]);
  }
  return selection_algorithm(ary, medians_len, medians_len / 2);
}

int
compare_num(const void * a, const void * b) {
  const kth_t * num_a = a;
  const kth_t * num_b = b;
  return * num_a - * num_b;
}

size_t
selection_algorithm(kth_t * ary, size_t len, size_t kth_smallest_num) {
  if (len <= 5) {
    qsort(ary, len, sizeof(kth_t), compare_num);
    return kth_smallest_num;
  }
  size_t pivot_i = median_of_medians(ary, len);
  size_t small_len = partition(ary, len, pivot_i);
  if (kth_smallest_num == small_len) return small_len;
  if (kth_smallest_num < small_len) {
    return selection_algorithm(ary, small_len, kth_smallest_num);
  } else {
    return (small_len + 1 + selection_algorithm(
            &ary[small_len + 1],
            len - small_len - 1,
            kth_smallest_num - small_len - 1));
  }
}

kth_t *
create_ary(size_t len) {
  return calloc(len, sizeof(kth_t));
}

point_t *
create_points(size_t len) {
  return calloc(len, sizeof(point_t));
}

size_t
get_pairs_len(size_t len) {
  size_t add = len % 2 == 1;
  return add ? (len + 1) / 2 : len / 2;
}

void
build_pairs(pair_t * pairs, point_t * points, size_t len) {
  size_t add = len % 2 == 1;
  size_t pairs_len = get_pairs_len(len);
  size_t i = 0;
  for (; i < pairs_len; i++) {
    pairs[i].a = points[i * 2];
    if (i == pairs_len - 1 && add) {
      pairs[i].b = points[0];
    } else {
      pairs[i].b = points[i * 2 + 1];
    }
  }
}

pair_t *
create_pairs(point_t * points, size_t len) {
  size_t pairs_len = get_pairs_len(len);
  pair_t * pairs = calloc(pairs_len, sizeof(pair_t));
  build_pairs(pairs, points, len);
  return pairs;
}

void
create_mid_point(point_t * a, point_t * b, point_t * mid) {
  mid->x = (a->x + b->x) / 2;
  mid->y = (a->y + b->y) / 2;
}

void
create_vector(point_t * a, point_t * b, point_t * vector) {
  vector->x = a->x - b->x;
  vector->y = a->y - b->y;
}

void
create_normal_vector(point_t * a, point_t * b, point_t * vector) {
  create_vector(a, b, vector);
  point_t clone = * vector;
  vector->x = clone.y;
  vector->y = - clone.x;
}

void
setup_mid_points(pair_t * pairs, size_t len, double y) {
  size_t pairs_len = get_pairs_len(len);
  size_t i = 0;
  printf("[pair]{center}{normal vector}{mid}\n");
  for (; i < pairs_len; i++) {
    pair_t * pair = &pairs[i];
    point_t mid;
    point_t normal;
    create_mid_point(&pair->a, &pair->b, &mid);
    create_normal_vector(&pair->a, &pair->b, &normal);
    // The x of point normal line on y = c
    // (y - mid.y) / (x - mid.x) = normal.y / normal.x
    // x = (y - mid.y) * normal.x / normal.y + mid.x
    if (normal.y == 0) {
      pairs[i].mid = DBL_MAX;
    } else {
      pairs[i].mid = (y - mid.y) * normal.x / normal.y + mid.x;
    }
    printf("[%.0lf %.0lf,%.0lf %.0lf]{%.2lf %.2lf}{%.0lf %.0lf} %.2lf\n",
           pairs[i].a.x,
           pairs[i].a.y,
           pairs[i].b.x,
           pairs[i].b.y,
           mid.x,
           mid.y,
           normal.x,
           normal.y,
           pairs[i].mid);
  }
}

double
find_median_midpoint(pair_t * pairs, size_t len) {
  size_t pairs_len = get_pairs_len(len);
  kth_t * ary = create_ary(pairs_len);
  size_t i = 0;
  for (; i < pairs_len; i++) {
    ary[i] = pairs[i].mid;
  }
  size_t median_i = selection_algorithm(ary, pairs_len, pairs_len / 2);
  kth_t mid = ary[median_i];
  free(ary);
  return mid;
}

double
points_x_distance(double a, double b) {
  return abs(a - b);
}

double
points_distance(point_t * a, point_t * b) {
  double x_dis = points_x_distance(a->x, b->x);
  double y_dis = points_x_distance(a->y, b->y);
  return sqrt(x_dis * x_dis + y_dis * y_dis);
}

size_t
double_pos(double x) {
  return x > 0.0001;
}

double
find_farthest_midpoint(double median_mid, point_t * points, size_t len) {
  size_t i = 0;
  double max = 0;
  size_t max_i = 0;
  for (; i < len; i++) {
    double dis = points_x_distance(points[i].x, median_mid);
    if (double_pos(dis - max)) {
      max = dis;
      max_i = i;
    }
  }
  double farthest_mid = points[max_i].x;
  return farthest_mid;
}

void
scan_points(point_t * points, size_t len) {
  size_t i = 0;
  for (; i < len; i++) {
    point_t * point = &points[i];
    scanf("(%lf%lf)", &point->x, &point->y);
    printf("(%.0lf %.0lf)", point->x, point->y);
  }
  puts("");
}

point_t *
select_farthest_point(pair_t * pair, double median_mid, double y) {
  point_t mid = {median_mid, y};
  return (points_distance(&pair->a, &mid) >
          points_distance(&pair->b, &mid)) ? &pair->a : &pair->b;
}

point_t *
select_closest_point(pair_t * pair, double median_mid, double y) {
  point_t mid = {median_mid, y};
  return (points_distance(&pair->a, &mid) <
          points_distance(&pair->b, &mid)) ? &pair->a : &pair->b;
}

size_t
prune_points(double median_mid, double farthest_mid,
             point_t * points, pair_t * pairs, size_t len, double y) {
  size_t pairs_len = get_pairs_len(len);
  size_t points_len = 0;
  size_t i = 0;
  double farthest_mid_side = farthest_mid - median_mid;
  for (; i < pairs_len; i++) {
    double mid_side = pairs[i].mid - median_mid;
    if (double_pos(farthest_mid_side) && double_pos(- mid_side) ||
        double_pos(- farthest_mid_side) && double_pos(mid_side)) {
      point_t * point = select_farthest_point(&pairs[i], median_mid, y);
      points[points_len++] = * point;
      point = select_closest_point(&pairs[i], median_mid, y);
      printf("prune [%.0lf %.0lf]\n", point->x, point->y);
    } else {
      points[points_len++] = pairs[i].a;
      points[points_len++] = pairs[i].b;
    }
  }
  if (points_len % 2 == 1 &&
      points_len == len) {
    points_len--;
  }
  return points_len;
}

double
find_center(point_t * points, size_t len, double y) {
  scan_points(points, len);
  pair_t * pairs = create_pairs(points, len);
  size_t i = 0;
  while (1) {
    setup_mid_points(pairs, len, y);
    double median_mid = find_median_midpoint(pairs, len);
    double farthest_mid = find_farthest_midpoint(median_mid, points, len);
    len = prune_points(median_mid, farthest_mid, points, pairs, len, y);
    build_pairs(pairs, points, len);
    printf("median mid %.2lf, farthest_mid mid %.2lf, len %zu\n",
           median_mid, farthest_mid, len);
    if (i == 4) break;
    i++;
    if (len <= 4) break;
  }
  free(pairs);
  return pairs[0].mid;
}

int
main(void) {
  size_t len;
  double y;
  scanf("%zu%lf\n", &len, &y);
  point_t * points = create_points(len);
  double center = find_center(points, len, y);
  printf("center %lf\n", center);
  free(points);
  return 0;
}
