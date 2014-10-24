#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int begin;
  int end;
} com_t;

int
cmp_coms(const void * a, const void * b) {
  const com_t * ap_a = a;
  const com_t * ap_b = b;
  return ap_a->begin - ap_b->begin;
}

void
sort_coms(com_t * aps, int len) {
  qsort(aps, len, sizeof(com_t), cmp_coms);
}

int
get_max(int a, int b) {
  return a > b ? a : b;
}

#define aps_len_storage_len 1040

int
max_aps_len(com_t * aps, int len) {
  static int aps_len_storage[aps_len_storage_len];
  memset(aps_len_storage, 0, aps_len_storage_len * sizeof(int));
  int * aps_len = aps_len_storage;
  int i = 0;
  int time = 0;
  int max = 0;
  for (; time < aps_len_storage_len; time++) {
    for (; aps[i].begin == time; i++) {
      aps_len[aps[i].end] = get_max(max + 1, aps_len[aps[i].end]);
    }
    //printf("aps_len[%d] %d, max %d\n", time, aps_len[time], max);
    aps_len[time] = get_max(aps_len[time], max);
    max = aps_len[time];
  }
  return max;
}

com_t *
create_coms(int len) {
  return calloc(len, sizeof(com_t));
}

int
main(void) {
  int slots_len, aps_len;
  while (scanf("%d%d", &slots_len, &aps_len) == 2) {
    com_t * aps = create_coms(aps_len);
    int i = 0;
    for (; i < aps_len; i++) {
      com_t * ap = &aps[i];
      scanf("%d%d", &ap->begin, &ap->end);
    }
    sort_coms(aps, aps_len);
    int max = max_aps_len(aps, aps_len);
    printf("%d\n", max);
    free(aps);
  }
  return 0;
}
