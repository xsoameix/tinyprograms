#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long num_t;

#define LEN 1100

num_t limit;
num_t src, dest;
num_t vlen, elen; // vertex, edge
num_t vs[LEN];
num_t ds[LEN]; // the path from source to every vertex
num_t mat[LEN][LEN];

void
scan_vs(void) {
  num_t i = 0;
  for (; i < vlen; i++) {
    scanf("%lld", &vs[i]);
    //printf("[%lld]", vs[i]);
  }
  //puts("");
}

void
scan_mat(void) {
  num_t i = 0;
  for (; i < vlen; i++) {
    num_t j = 0;
    for (; j < vlen; j++) {
      num_t cost;
      scanf("%lld", &cost);
      //printf("%lld ", cost);
      mat[i][j] = cost == -1 ? INT_MAX : cost;
    }
    //puts("");
  }
}

void
belloman_ford(void) {
  num_t i = 0;
  for (; i < vlen; i++) {
    ds[i] = INT_MAX;
  }
  ds[src] = 0;
  num_t vi = 0;
  for (; vi < vlen - 1; vi++) {
    num_t from = 0;
    for (; from < vlen; from++) {
      num_t to = 0;
      for (; to < vlen; to++) {
        if (ds[from] == INT_MAX ||
            mat[from][to] == INT_MAX) continue;
        //printf("%lld -> %lld  %lld  %s\n",
        //       from, to, vs[to], vs[to] < limit ? "x" : "o");
        if (vs[from] < limit || vs[to] < limit) continue;
        num_t path = ds[from] + mat[from][to];
        if (path < ds[to]) {
          ds[to] = path;
        }
      }
    }
  }
}

void
scan_src_dest(void) {
  while (1) {
    scanf("%lld", &src);
    scanf("%lld", &dest);
    if (src == -1 && dest == -1) break;
    belloman_ford();
    if (ds[dest] == INT_MAX) {
      printf("*\n");
    } else {
      printf("%lld\n", ds[dest]);
    }
  }
}

int
main(void) {
  while (1) {
    scanf("%lld%lld", &limit, &vlen);
    if (limit == 0 && vlen == 0) break;
    scan_vs();
    scan_mat();
    scan_src_dest();
  }
  return 0;
}
