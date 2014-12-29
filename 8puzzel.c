#include <stdio.h>

typedef long long num_t;

#define LEN 3
#define MAX_REC 51 // max record len

typedef struct {
  num_t v[LEN][LEN]; // value
  num_t row, col;
  num_t cost;
  num_t lv; // level
} rec_t; // record

num_t lim;
rec_t puz;
rec_t final = {
  {
    {1,2,3},
    {8,0,4},
    {7,6,5}
  },
  1, 1,
  0
};

num_t
find_cost(rec_t * state) {
  num_t cost = 0;
  num_t i = 0;
  for (; i < LEN; i++) {
    num_t j = 0;
    for (; j < LEN; j++) {
      if (state->v[i][j] != final.v[i][j]) {
        cost++;
      }
    }
  }
  return cost;
}

num_t
min_rec(rec_t * rec, num_t len) {
  num_t min_cost = rec[0].cost;
  num_t min_i = 0;
  num_t i = 1;
  for (; i < len; i++) {
    if (rec[i].cost < min_cost) {
      min_cost = rec[i].cost;
      min_i = i;
    }
  }
  return min_i;
}

void
swap_rec(rec_t * rec, num_t i, num_t j) {
  rec_t tmp = rec[i];
  rec[i] = rec[j];
  rec[j] = tmp;
}

void
swap_cel(rec_t * rec, num_t i, num_t j) {
  num_t v = rec->v[rec->row][rec->col];
  rec->v[rec->row][rec->col] = rec->v[i][j];
  rec->v[i][j] = v;
  rec->row = i;
  rec->col = j;
}

void
prec(rec_t * rec) {
  printf(" --- %lld ---\n", rec->cost);
  num_t i = 0;
  for (; i < LEN; i++) {
    num_t k = 0;
    for (; k < rec->lv; k++) {
      printf(" ");
    }
    num_t j = 0;
    for (; j < LEN; j++) {
      printf("%2lld ", rec->v[i][j]);
    }
    puts("");
  }
}

void
can(void) {
  num_t total = 0;
  static rec_t recs[1500];
  num_t rec_i = 0;
  num_t rec_len = 0;
  recs[rec_len++] = puz;
  while (1) {
    num_t i = min_rec(recs, rec_len);
    swap_rec(recs, i, rec_len - 1);
    rec_len--;
    rec_t now = recs[rec_len];
    prec(&now);
    static num_t stop = 0;
    if (stop++ == 21) break;
    if (find_cost(&now) == 0) {
      printf("YES\n");
      break;
    }
    if (now.lv == lim) {
      printf("NO\n");
      break;
    }
    if (now.col < LEN - 1) {
      rec_t tbl = now;
      swap_cel(&tbl, tbl.row, tbl.col + 1);
      tbl.cost = find_cost(&tbl);
      tbl.lv++;
      recs[rec_len++] = tbl;
    }
    if (now.row < LEN - 1) {
      rec_t tbl = now;
      swap_cel(&tbl, tbl.row + 1, tbl.col);
      tbl.cost = find_cost(&tbl);
      tbl.lv++;
      recs[rec_len++] = tbl;
    }
    if (now.col > 0) {
      rec_t tbl = now;
      swap_cel(&tbl, tbl.row, tbl.col - 1);
      tbl.cost = find_cost(&tbl);
      tbl.lv++;
      recs[rec_len++] = tbl;
    }
    if (now.row > 0) {
      rec_t tbl = now;
      swap_cel(&tbl, tbl.row - 1, tbl.col);
      tbl.cost = find_cost(&tbl);
      tbl.lv++;
      recs[rec_len++] = tbl;
    }
  }
}

int
main(void) {
  while (1) {
    scanf("%lld", &lim);
    if (lim == 0) break;
    num_t i = 0;
    for (; i < LEN; i++) {
      num_t j = 0;
      for (; j < LEN; j++) {
        scanf("%lld", &puz.v[i][j]);
        if (puz.v[i][j] == 0) {
          puz.row = i;
          puz.col = j;
        }
      }
    }
    puz.cost = find_cost(&puz);
    puz.lv = 0;
    can();
  }
  return 0;
}
