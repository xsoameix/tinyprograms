:struct Town {
  int id;
  int limit;
  int cost;
}

int
:cost(self) {
  list_t * list = List.new();
  :Ary.each @towns { |town i|
    town->cost = INT_MAX;
    list·add(Node.new(town));
  }
  @towns·first->cost = 0;
  while (list·len) {
    town_t * from = list·remove(:Ary.min_by(list, Town, cost));
    :Ary.each @towns { |to i|
      if (from->limit < @people || to->limit < @people) continue;
      int * road = ·get(from->id, i);
      if (* road == -1) continue;
      if (from->cost + * road < to->cost) {
        to->cost = from->cost + * road;
      }
    }
  }
  return @towns·last->cost;
}

int
main(void) {
  int people, towns_len;
  while (scanf("%d%d", &people, &towns_len) == 2) {
    list_t * towns = :Ary.new(Town, towns_len);
    matrix_t * tmat = :Matrix.new(Town, towns_len);
    :Ary.each towns { |town i|
      town->id = i;
      scanf("%d", &town->limit);
    }
    :Matrix.each tmat { |road row col|
      scanf("%d", road);
    }
    int cost = tmat·cost(towns, people);
    if (cost == INT_MAX) {
      printf("*\n");
    } else {
      printf("%d\n", cost);
    }
  }
  return 0;
}
