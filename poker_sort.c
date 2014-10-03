#include <stdio.h>
#include <stdlib.h>

// input file:
//  tabe %:r-input
//
// Compile command:
//  :Compile

#define CARDS_LEN 5
#define CARD_SIZE 2 + 1
#define CARD_TYPES_LEN 4

typedef struct card {
  int id;
  int type;
} card_t;

typedef struct group {
  int      cards_len;
  card_t * cards[CARDS_LEN - 1];
} group_t;

typedef struct stub {
  int     id;
  card_t  cards[CARDS_LEN];
  int     type;
  int     groups_len;
  group_t groups[CARDS_LEN];
} stub_t;

enum card_id {
  card_zilch,
  card_one_pair,
  card_two_pairs,
  card_three_of_a_kind,
  card_straight,
  card_flush,
  card_fullhouse,
  card_four_of_a_kind,
  card_straight_flush,
  card_royal_flush
};

char * card_ids[] = {
  "zilch",
  "one_pair",
  "two_pairs",
  "three_of_a_kind",
  "straight",
  "flush",
  "fullhouse",
  "four_of_a_kind",
  "straight_flush",
  "royal_flush"
};

enum card_type {
  card_d,
  card_c,
  card_h,
  card_s
};

int
cmp_cards(const void * a, const void * b) {
  const card_t * card_a = a;
  const card_t * card_b = b;
  return card_a->id - card_b->id;
}

void
sort_cards(stub_t * stub) {
  card_t * cards = stub->cards;
  qsort(cards, CARDS_LEN, sizeof(card_t), cmp_cards);
}

int
parse_card_type(char type) {
  if (type == 'S') return card_s;
  if (type == 'H') return card_h;
  if (type == 'C') return card_c;
  if (type == 'D') return card_d;
  return -1;
}

int
parse_card_id(char id) {
  if (id >= '2' &&
      id <= '9') {
    return id - '0';
  }
  if (id == '0') return 10;
  if (id == 'J') return 11;
  if (id == 'Q') return 12;
  if (id == 'K') return 13;
  if (id == '1') return 14;
  return -1;
}

int
parse_stub_type(const stub_t * stub) {
  const card_t * cards = stub->cards;
  if (cards[0].type == cards[1].type && cards[0].id + 1 == cards[1].id &&
      cards[1].type == cards[2].type && cards[1].id + 1 == cards[2].id &&
      cards[2].type == cards[3].type && cards[2].id + 1 == cards[3].id &&
      cards[3].type == cards[4].type && cards[3].id + 1 == cards[4].id &&
      cards[4].id == 14) {
    return card_royal_flush;
  }
  if (cards[0].type == cards[1].type && cards[0].id + 1 == cards[1].id &&
      cards[1].type == cards[2].type && cards[1].id + 1 == cards[2].id &&
      cards[2].type == cards[3].type && cards[2].id + 1 == cards[3].id &&
      cards[3].type == cards[4].type &&
      (cards[3].id + 1 == cards[4].id ||
       cards[3].id == 5 && cards[4].id == 14)) {
    return card_straight_flush;
  }
  if ((cards[0].id == cards[1].id ||
       cards[3].id == cards[4].id) &&
      cards[1].id == cards[2].id &&
      cards[2].id == cards[3].id) {
    return card_four_of_a_kind;
  }
  if (cards[0].id == cards[1].id &&
      (cards[1].id == cards[2].id ||
       cards[2].id == cards[3].id) &&
      cards[3].id == cards[4].id) {
    return card_fullhouse;
  }
  int card_i = 0;
  int types[CARD_TYPES_LEN] = {0};
  for (; card_i < CARDS_LEN; card_i++) {
    types[cards[card_i].type]++;
  }
  if (types[0] == 5 ||
      types[1] == 5 ||
      types[2] == 5 ||
      types[3] == 5) {
    return card_flush;
  }
  if (cards[0].id + 1 == cards[1].id &&
      cards[1].id + 1 == cards[2].id &&
      cards[2].id + 1 == cards[3].id &&
      (cards[3].id + 1 == cards[4].id ||
       cards[3].id == 5 && cards[4].id == 14)) {
    return card_straight;
  }
  if (cards[0].id == cards[1].id &&
      cards[1].id == cards[2].id ||
      cards[1].id == cards[2].id &&
      cards[2].id == cards[3].id ||
      cards[2].id == cards[3].id &&
      cards[3].id == cards[4].id) {
    return card_three_of_a_kind;
  }
  if (cards[0].id == cards[1].id &&
      cards[2].id == cards[3].id ||
      cards[0].id == cards[1].id &&
      cards[3].id == cards[4].id ||
      cards[1].id == cards[2].id &&
      cards[3].id == cards[4].id) {
    return card_two_pairs;
  }
  if (cards[0].id == cards[1].id ||
      cards[1].id == cards[2].id ||
      cards[2].id == cards[3].id ||
      cards[3].id == cards[4].id) {
    return card_one_pair;
  }
  return card_zilch;
}

card_t *
reorder_straight(stub_t * stub) {
  int type = stub->type;
  card_t * cards = stub->cards;
  if (type == card_straight_flush ||
      type == card_straight) {
    if (cards[CARDS_LEN - 2].id == 5 &&
        cards[CARDS_LEN - 1].id == 14) {
      card_t first_card = cards[CARDS_LEN - 1];
      first_card.id = 1;
      cards[4] = cards[3];
      cards[3] = cards[2];
      cards[2] = cards[1];
      cards[1] = cards[0];
      cards[0] = first_card;
    }
  }
}

int
cmp_group(const void * a, const void * b) {
  const group_t * group_a = a;
  const group_t * group_b = b;
  return (group_a->cards_len != 0 &&
          group_a->cards_len == group_b->cards_len ?
          group_b->cards[0]->id - group_a->cards[0]->id :
          group_b->cards_len    - group_a->cards_len);
}

int
cmp_group_cards(const void * a, const void * b) {
  card_t ** card_a = (card_t **) a;
  card_t ** card_b = (card_t **) b;
  return (* card_b)->type - (* card_a)->type;
}

void
sort_groups(group_t * groups, int groups_len) {
  qsort(groups, groups_len, sizeof(group_t), cmp_group);
  int group_i = 0;
  for (; group_i < groups_len; group_i++) {
    group_t * group = &groups[group_i];
    qsort(group->cards, group->cards_len, sizeof(card_t *), cmp_group_cards);
  }
}

void
set_groups(stub_t * stub) {
  card_t * cards = stub->cards;
  int i = 0;
  int id = -1;
  group_t * groups = stub->groups;
  for (; i < CARDS_LEN; i++) {
    if (cards[i].id != id) {
      id = cards[i].id;
      stub->groups_len++;
    }
    group_t * group = &groups[stub->groups_len - 1];
    group->cards[group->cards_len++] = &cards[i];
  }
  sort_groups(groups, stub->groups_len);
}

int
cmp_group_by_id(const stub_t * stub_a, const stub_t * stub_b) {
  int group_i = 0;
  for (; group_i < stub_a->groups_len; group_i++) {
    const group_t * group_a = &stub_a->groups[group_i];
    const group_t * group_b = &stub_b->groups[group_i];
    int card_i = 0;
    for (; card_i < group_a->cards_len; card_i++) {
      const card_t * card_a = group_a->cards[card_i];
      const card_t * card_b = group_b->cards[card_i];
      if (card_a->id == card_b->id) break;
      return card_b->id - card_a->id;
    }
  }
  return 0;
}

int
cmp_group_by_type(const stub_t * stub_a, const stub_t * stub_b) {
  int group_i = 0;
  for (; group_i < stub_a->groups_len; group_i++) {
    const group_t * group_a = &stub_a->groups[group_i];
    const group_t * group_b = &stub_b->groups[group_i];
    int card_i = 0;
    for (; card_i < group_a->cards_len; card_i++) {
      const card_t * card_a = group_a->cards[card_i];
      const card_t * card_b = group_b->cards[card_i];
      if (card_a->type == card_b->type) continue;
      return card_b->type - card_a->type;
    }
  }
  return 0;
}

int
cmp_stubs_groups(const stub_t * stub_a, const stub_t * stub_b) {
  int ret;
  ret = cmp_group_by_id(stub_a, stub_b);
  if (ret != 0) return ret;
  ret = cmp_group_by_type(stub_a, stub_b);
  if (ret != 0) return ret;
}

int
cmp_stubs(const void * a, const void * b) {
  const stub_t * stub_a = a;
  const stub_t * stub_b = b;
  int type_a = stub_a->type;
  int type_b = stub_b->type;
  if (type_a != type_b) {
    return type_b - type_a;
  }
  return cmp_stubs_groups(stub_a, stub_b);
}

void
sort_stubs(stub_t * stubs, int len) {
  qsort(stubs, len, sizeof(stub_t), cmp_stubs);
}

stub_t *
create_stubs(int len) {
  return calloc(len, sizeof(stub_t));
}

void
scan_card(card_t * card) {
  char type;
  scanf("%c", &type);
  card->type = parse_card_type(type);
  char id;
  scanf("%c", &id);
  card->id = parse_card_id(id);
}

void
scan_cards(card_t * cards) {
  int card_i = 0;
  for (; card_i < CARDS_LEN; card_i++) {
    scan_card(&cards[card_i]);
    if (card_i != CARDS_LEN - 1) {
      scanf(" ");
    }
  }
  scanf("\n");
}

void
build_stubs(stub_t * stubs, int stubs_len) {
  int stub_i = 0;
  for (; stub_i < stubs_len; stub_i++) {
    stub_t * stub = &stubs[stub_i];
    sort_cards(stub);
    stub->type = parse_stub_type(stub);
    reorder_straight(stub);
    set_groups(stub);
  }
  sort_stubs(stubs, stubs_len);
}

void
print_stubs(stub_t * stubs, int stubs_len) {
  int stub_i = 0;
  for (; stub_i < stubs_len; stub_i++) {
    stub_t * stub = &stubs[stub_i];
    printf("%d", stub->id);
    if (stub_i != stubs_len - 1) {
      printf(" ");
    }
  }
  printf("\n");
}

void
scan_stubs(void) {
  int stub_i = 0;
  int stubs_len;
  scanf("%d\n", &stubs_len);
  stub_t * stubs = create_stubs(stubs_len);
  for (; stub_i < stubs_len; stub_i++) {
    stub_t * stub = &stubs[stub_i];
    stub->id = stub_i + 1;
    scan_cards(stub->cards);
  }
  build_stubs(stubs, stubs_len);
  print_stubs(stubs, stubs_len);
  free(stubs);
}

void
scan_arys(void) {
  int ary_i = 0;
  int arys_len;
  scanf("%d\n", &arys_len);
  for (; ary_i < arys_len; ary_i++) {
    scan_stubs();
  }
}

int
main(void) {
  scan_arys();
  return 0;
}
