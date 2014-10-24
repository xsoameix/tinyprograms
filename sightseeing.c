#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  int limit;
} citi_t;

typedef struct {
  citi_t * cities;
  int src;
  int dest;
} road_t;

typedef struct {
  int groups_len;
  int * groups;
} set_t;

int
get_min(int a, int b) {
  return a < b ? a : b;
}

set_t *
set_new(int len) {
  //set_t * set = calloc(1, sizeof(set_t) + len * sizeof(int));
  static char set_storage[900];
  memset(set_storage, 0, sizeof(set_storage));
  set_t * set = (void *) set_storage;
  set->groups_len = len;
  set->groups = (void *) set + sizeof(set_t);
  int i = 0;
  for (; i < len; i++) {
    set->groups[i] = i;
  }
  return set;
}

int
set_find(set_t * set, int i) {
  int * g = set->groups;
  if (i == g[i]) return i;
  g[i] = set_find(set, g[i]);
  return g[i];
}

void
set_merge(set_t * set, int to, int from) {
  to = set_find(set, to);
  from = set_find(set, from);
  if (to == from) return;
  set->groups_len--;
  set->groups[from] = to;
}

int
set_eq(set_t * set, int a, int b) {
  return set_find(set, a) == set_find(set, b);
}

int
set_groups_len(set_t * set) {
  return set->groups_len;
}

int
road_limit(const road_t * road) {
  citi_t * cities = road->cities;
  return (road->src < road->dest ?
          cities[road->dest].limit :
          cities[road->src].limit);
}

int
cmp_roads(const void * a, const void * b) {
  const road_t * road_a = a;
  const road_t * road_b = b;
  return road_limit(road_b) - road_limit(road_a);
}

void
sort_roads(road_t * roads, int len) {
  qsort(roads, len, sizeof(road_t), cmp_roads);
}

int
max_people_to_travel(int src, int dest,
                     citi_t * cities, int cities_len,
                     road_t * roads, int roads_len) {
  int max = cities[dest].limit;
  set_t * set = set_new(cities_len);
  int i = 0;
  for (; i < roads_len; i++) {
    if (set_eq(set, src, dest)) break;
    road_t * road = &roads[i];
    if (!set_eq(set, road->src, road->dest)) {
      set_merge(set, road->src, road->dest);
    }
    max = road_limit(road);
  }
  //free(set);
  // add tour
  max--;
  return max;
}

void
create_cities_and_roads(citi_t ** cities, int cities_len,
                        road_t ** roads, int roads_len) {
  int cities_size = cities_len * sizeof(citi_t); // max: 100 * 2
  int roads_size = roads_len * sizeof(road_t); // max: 100^2 * 3
  //* cities = calloc(1, cities_size + roads_size);
  static char cities_storage[30200];
  memset(cities_storage, 0, sizeof(cities_storage));
  * cities = (void *) cities_storage;
  * roads = (void *) * cities + cities_size;
}

void
scan_cities_and_roads(citi_t * cities, int cities_len,
                      road_t * roads, int roads_len) {
  int citi_i = 0;
  for (; citi_i < cities_len; citi_i++) {
    int id, limit;
    scanf("%d%d", &id, &limit);
    id--;
    cities[id].id = id;
    cities[id].limit = limit;
  }
  int road_i = 0;
  for (; road_i < roads_len; road_i++) {
    int src, dest;
    scanf("%d%d", &src, &dest);
    src--, dest--;
    roads[road_i].cities = cities;
    roads[road_i].src = src;
    roads[road_i].dest = dest;
  }
}

int
main(void) {
  while (1) {
    int cities_len, roads_len;
    scanf("%d%d", &cities_len, &roads_len);
    if (cities_len == 0 &&
        roads_len == 0) break;
    int src, dest, people;
    scanf("%d%d%d", &src, &dest, &people);
    src--, dest--;
    citi_t * cities;
    road_t * roads;
    create_cities_and_roads(&cities, cities_len, &roads, roads_len);
    scan_cities_and_roads(cities, cities_len, roads, roads_len);
    sort_roads(roads, roads_len);
    int limit = max_people_to_travel(
        src, dest, cities, cities_len, roads, roads_len);
    //printf("limit %d, ", limit);
    printf("%d is the minimum number of trips.\n",
           (people + limit - 1) / limit);
    //free(cities);
  }
  return 0;
}
