#include <stdio.h>
#include <stdlib.h>

void
print_ary(int * ary, size_t len) {
  size_t i = 0;
  for (; i < len; i++) {
    printf("%d ", ary[i]);
  }
  printf("\n");
}

int *
create_ary(int len) {
  return calloc(len, sizeof(int));
}

int
cmp_npc(const void * a, const void * b) {
  const int * npc_a = a;
  const int * npc_b = b;
  return * npc_a - * npc_b;
}

int
match_height_sum(int * npcs, int npc_len,
                 int * players, int players_len,
                 int height_sum) {
  int matches = 0;
  int player_i = 0;
  for (; player_i < players_len; player_i++) {
    int npc_height = height_sum - players[player_i];
    int * npc_i = bsearch(&npc_height, npcs, npc_len, sizeof(int), cmp_npc);
    if (npc_i != NULL) {
      matches++;
    }
  }
  return matches;
}

int
main(void) {
  int npcs_len, players_len, height_sum;
  while (1) {
    scanf("%d%d%d", &npcs_len, &players_len, &height_sum);
    if (npcs_len == 0 &&
        players_len == 0 &&
        height_sum == 0) {
      break;
    }
    int * npcs = create_ary(npcs_len);
    int * players = create_ary(players_len);
    int i = 0;
    for (; i < npcs_len; i++) {
      scanf("%d", &npcs[i]);
    }
    i = 0;
    for (; i < players_len; i++) {
      scanf("%d", &players[i]);
    }
    int matches = match_height_sum(npcs, npcs_len,
                                   players, players_len,
                                   height_sum);
    printf("%d\n", matches);
  }
  return 0;
}
