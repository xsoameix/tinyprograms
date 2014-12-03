#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long num_t;

#define LEN 1100

num_t src, dest;
num_t vlen, elen; // vertex, edge
num_t vs[LEN];
num_t ds[LEN]; // the path from source to every vertex
num_t mat[LEN][LEN];

void
scan_vs(void) {
  num_t i = 0;
  for (; i < vlen; i++) {
    vs[i] = INT_MAX;
  }
  i = 0;
  for (; i < vlen; i++) {
    num_t id;
    scanf("%lld", &id);
    scanf("%lld", &vs[id - 1]);
  }
}

void
scan_mat(void) {
  num_t i = 0;
  for (; i < vlen; i++) {
    num_t j = 0;
    for (; j < vlen; j++) {
      mat[i][j] = INT_MAX;
    }
  }
  num_t ei = 0;
  for (; ei < elen; ei++) {
    num_t from, to;
    scanf("%lld", &from);
    scanf("%lld", &to);
    from--, to--;
    scanf("%lld", &mat[from][to]);
    mat[to][from] = mat[from][to];
  }
}

void
belloman_ford(void) {
  num_t i = 0;
  for (; i < vlen; i++) {
    ds[i] = INT_MAX;
  }
  ds[src] = vs[src];
  num_t vi = 0;
  for (; vi < vlen - 1; vi++) {
    num_t from = 0;
    for (; from < vlen; from++) {
      num_t to = 0;
      for (; to < vlen; to++) {
        if (ds[from] == INT_MAX ||
            mat[from][to] == INT_MAX) continue;
        num_t path = ds[from] + mat[from][to] + vs[to];
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
    src--, dest--;
    belloman_ford();
    if (ds[dest] == INT_MAX) {
      printf("0\n");
    } else {
      printf("%lld\n", ds[dest]);
    }
  }
}

int
main(void) {
  while (1) {
    scanf("%lld%lld", &vlen, &elen);
    if (!vlen && !elen) break;
    scan_vs();
    scan_mat();
    scan_src_dest();
  }
  return 0;
}
