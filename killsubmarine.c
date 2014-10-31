#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef struct {
  int x;
  int y;
  int origin_x;
  int origin_y;
} submarine_t;

submarine_t *
create_submarines(int len) {
  return calloc(len, sizeof(submarine_t));
}

double
subm_slop(const submarine_t * sub) {
  if (sub->x == sub->origin_x) return -DBL_MAX;
  return (double) (sub->y - sub->origin_y) / (sub->x - sub->origin_x);
}

int
cmp_submarines(const void * a, const void * b) {
  const submarine_t * sub_a = a;
  const submarine_t * sub_b = b;
  if (subm_slop(sub_a) < subm_slop(sub_b)) {
    return -1;
  } else if (subm_slop(sub_a) == subm_slop(sub_b)) {
    return 0;
  } else {
    return 1;
  }
}

void
sort_submarines(submarine_t * submarines, int submarines_len,
                submarine_t * submarine) {
  int origin_i = 0;
  for (; origin_i < submarines_len; origin_i++) {
    submarines[origin_i].origin_x = submarine->x;
    submarines[origin_i].origin_y = submarine->y;
  }
  qsort(submarines, submarines_len, sizeof(submarine_t), cmp_submarines);
  int i = 0;
  printf("[%d %d] ", submarine->x, submarine->y);
  for (; i < submarines_len; i++) {
    double prev = subm_slop(&submarines[i]);
    double prev_d = prev == -DBL_MAX ? -9.99 : prev;
    printf("[%d %d %.3f]", submarines[i].x, submarines[i].y, prev_d);
  }
  puts("");
}

int
same_submarines_len(submarine_t * submarines, int submarines_len) {
  double prev = subm_slop(&submarines[0]);
  int len = 1;
  int i = 1;
  for (; i < submarines_len; i++) {
    double next = subm_slop(&submarines[i]);
    double prev_d = prev == -DBL_MAX ? -9.99 : prev;
    double next_d = next == -DBL_MAX ? -9.99 : next;
    printf(" i %d [%3.3f][%d %d %3.3f]\n", i, prev_d, submarines[i].x, submarines[i].y, next_d);
    if (fabs(next - prev) <= 0.0001) {
      len++;
    } else {
      break;
    }
    static stop = 0;
    stop++;
    if (stop == 45) exit(0);
  }
  return len;
}

int
longest_same_submarines(submarine_t * submarines, int submarines_len,
                        int * len_ret) {
  int longest_i = 0;
  int max_len = 0;
  int len = 0;
  int each_len = 0;
  int i = 1;
  for (; i < submarines_len; i += each_len) {
    each_len = same_submarines_len(&submarines[i], submarines_len - i);
    if (each_len > max_len) {
      max_len = each_len;
      longest_i = i;
    }
    static stop = 0;
    stop++;
    if (stop == 45) exit(0);
  }
  * len_ret = max_len + 1;
  return longest_i;
}

submarine_t *
clone_submarines(submarine_t * submarines, int submarines_len) {
  submarine_t * sub = create_submarines(submarines_len);
  int i = 0;
  for (; i < submarines_len; i++) {
    sub[i] = submarines[i];
  }
  return sub;
}

int
select_submarines(submarine_t * submarines, int submarines_len,
                  int * selected_len) {
  submarine_t * clone = clone_submarines(submarines, submarines_len);
  int longest_len = 0;
  int longest_i = 0;
  int i = 0;
  for (; i < submarines_len; i++) {
    sort_submarines(clone, submarines_len, &submarines[i]);
    int len = 0;
    longest_same_submarines(clone, submarines_len, &len);
    if (len > longest_len) {
      longest_len = len;
      longest_i = i;
    }
  }
  sort_submarines(clone, submarines_len, &submarines[longest_i]);
  int selected_i =
      longest_same_submarines(clone, submarines_len, selected_len);
  printf("selected_i %d, selected_len %d\n",
         selected_i, * selected_len);
  free(clone);
  return selected_i;
}

int
main(void) {
  int submarines_len, origin_y;
  while (1) {
    scanf("%d%d", &submarines_len, &origin_y);
    if (submarines_len == 0 &&
        origin_y == 0) break;
    int i = 0;
    submarine_t * submarines = create_submarines(submarines_len);
    for (; i < submarines_len; i++) {
      scanf("%d%d", &submarines[i].x, &submarines[i].y);
    }
    int len;
    i = select_submarines(submarines, submarines_len, &len);
    len = i + len;
    for (; i < len; i++) {
      printf("%d %d\n", submarines[i].x, submarines[i].y);
    }
    free(submarines);
  }
  return 0;
}
