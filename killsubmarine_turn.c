#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

typedef struct {
  int x;
  int y;
} subm_t;

typedef struct rank {
  int rank;
  struct rank * first;
  struct rank * prev;
  subm_t * subm;
} rank_t;

typedef struct {
  int i;
  rank_t * rank;
} rankp_t;

subm_t *
create_subms(int len) {
  return calloc(len, sizeof(subm_t));
}

int
cmp_ranks_in_y(const void * a, const void * b) {
  const rank_t * rank_a = a;
  const rank_t * rank_b = b;
  return rank_a->subm->y - rank_b->subm->y;
}

int
cmp_ranks_in_x(const void * a, const void * b) {
  const rankp_t * rank_a = a;
  const rankp_t * rank_b = b;
  return rank_b->rank->subm->x - rank_a->rank->subm->x;
}

void
sort_ranks_in_y(rank_t * ranks, int ranks_len) {
  qsort(ranks, ranks_len, sizeof(rank_t), cmp_ranks_in_y);
}

void
sort_ranks_in_x(rankp_t * ranks, int ranks_len) {
  qsort(ranks, ranks_len, sizeof(rankp_t), cmp_ranks_in_x);
}

int
lower_bit(int n) {
  return n & -n;
}

void
print_ranks(rankp_t * ranks, int ranks_len) {
  int i = 0;
  for (; i < ranks_len; i++) {
    rank_t * rank = ranks[i].rank;
    printf("[%d %d] i %d\n", rank->subm->x, rank->subm->y, ranks[i].i);
  }
}

rank_t *
select_subms(subm_t * subms, int subms_len, rank_t ** ranks_ret) {
  rank_t * ranks = calloc(subms_len, sizeof(rank_t));
  int i = 0;
  for (; i < subms_len; i++) {
    ranks[i].subm = &subms[i];
  }
  sort_ranks_in_y(ranks, subms_len);
  subm_t * min_y = ranks[0].subm;
  rankp_t * rankps = calloc(subms_len, sizeof(rankp_t));
  i = 0;
  for (; i < subms_len; i++) {
    rankps[i].i = i;
    rankps[i].rank = &ranks[i];
  }
  //print_ranks(rankps, subms_len);
  sort_ranks_in_x(rankps, subms_len);
  //print_ranks(rankps, subms_len);
  i = 0;
  for (; i < subms_len; i++) {
    int rank_i = rankps[i].i;
    printf("i %d\n", i);
    rank_t * rank = rankps[i].rank;
    rank_t * prev = rank - 1;
    while (rank_i < subms_len) {
      if (rank->subm == min_y) {
        ranks[rank_i].first = rank;
        ranks[rank_i].rank = 1;
      } else if (prev->rank + 1 > ranks[rank_i].rank) {
        ranks[rank_i].first = rank;
        ranks[rank_i].prev = prev->first;
        ranks[rank_i].rank = prev->rank + 1;
      }
      rank_i += lower_bit(rank_i + 1);
      int t = 0;
      for (; t < subms_len; t++) {
        printf("%d ", ranks[t].rank);
      }
      puts("");
    }
  }
  free(rankps);
  rank_t * rank_ret = NULL;
  int max_rank = 0;
  i = 0;
  for (; i < subms_len; i++) {
    int rank = ranks[i].rank;
    if (rank > max_rank) {
      max_rank = rank;
      rank_ret = &ranks[i];
    }
  }
  * ranks_ret = ranks;
  return rank_ret;
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
    rank_t * ranks;
    rank_t * rank = select_subms(subms, subms_len, &ranks);
    int len = rank->rank;
    printf("%d\n", len);
    i = 0;
    for (; i < len; i++) {
      printf("%d %d\n", rank->subm->x, rank->subm->y);
      rank = rank->prev;
    }
    free(ranks);
    free(subms);
  }
  return 0;
}
