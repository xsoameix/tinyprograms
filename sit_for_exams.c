#include <limits.h>

:class Town {

  struct {
    int id;
    int limit;
    int cost;
  }
}

:class Towns < Ary {}

· *
:new(int len) { return super(&Towns, len); }

int
:size(void) { return sizeof(town_t); }

void
:scan(self) {
  int i = 0;
  for (; i < @len; i++) {
    town_t * town = ·get(i);
    town->id = i;
    scanf("%d", &town->limit);
  }
}

void
:print(self) {
  int i = 0;
  for (; i < @len; i++) {
    town_t * town = ·get(i);
    printf("limit %d, cost %d\n", town->limit, town->cost);
  }
}

:class Tnode < Lnode {}

· *
:new(town_t * town) { return super(&Tnode, town); }

:class Tlist < List {}

· *
:new(void) { return super(&Tlist); }

int
:cmp(self, void * a, void * b) {
  town_t * town_a = a;
  town_t * town_b = b;
  return town_a->cost - town_b->cost;
}

void
:print(self) {
  tnode_t * node = (tnode_t *) @head;
  printf("[");
  for (; node; node = node->back) {
    town_t * town = node->obj;
    printf("%d: ", town->id);
    if (town->cost == INT_MAX) {
      printf("max ");
    } else {
      printf("%d ", town->cost);
    }
  }
  printf("]\n");
}

:class Road {

  struct {
    int cost;
  }
}

:class Tmat < Matrix {

  struct {
    int people;
    towns_t * towns;
  }
}

· *
:new(towns_t * towns, int people) {
  int len = towns·len;
  · * self = calloc(1, sizeof(·) + len * len * Tmat.size());
  @class = &Tmat;
  @len = len;
  @objs = (void *) self + sizeof(·);
  @towns = towns;
  @people = people;
  return self;
}

int
:size(void) { return sizeof(road_t); }

void
:scan(self) {
  int row = 0;
  for (; row < @len; row++) {
    int col = 0;
    for (; col < @len; col++) {
      road_t * road = ·get(row, col);
      scanf("%d", &road->cost);
    }
  }
}

int
:cost(self) {
  towns_t * towns = @towns;
  town_t * town = towns·first;
  town->cost = 0;
  int i = 1;
  for (; i < towns·len; i++) {
    town_t * town = towns·get(i);
    town->cost = INT_MAX;
  }
  tlist_t * list = Tlist.new();
  i = 0;
  for (; i < towns·len; i++) {
    town_t * town = towns·get(i);
    list·add(Tnode.new(town));
  }
  while (list·len) {
    tnode_t * min = list·min;
    town_t * from = min->obj;
    //list·print;
    list·remove(min);
    int i = 0;
    for (; i < ·len; i++) {
      town_t * to = towns·get(i);
      if (from->limit < @people ||
          to->limit < @people) continue;
      road_t * road = ·get(from->id, i);
      if (road->cost == -1) continue;
      int cost = from->cost + road->cost;
      //printf("from %d, to %d, cost %d + %d = %d\n",
      //       from->id, to->id,
      //       from->cost, road->cost, cost);
      if (cost < to->cost) {
        to->cost = cost;
      }
    }
  }
  list·free;
  town_t * last = towns·last;
  return last->cost;
}

int
main(void) {
  int people, towns_len;
  while (scanf("%d%d", &people, &towns_len) == 2) {
    towns_t * towns = Towns.new(towns_len);
    tmat_t * tmat = Tmat.new(towns, people);
    towns·scan;
    tmat·scan;
    int cost = tmat·cost;
    if (cost == INT_MAX) {
      printf("*\n");
    } else {
      printf("%d\n", cost);
    }
    //towns·print;
    tmat·free;
    towns·free;
  }
  return 0;
}
