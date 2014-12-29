#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>

typedef uint8_t utf_t;

// Fowler–Noll–Vo hash function
typedef utf_t * h_data_t;
typedef uintptr_t h_size_t;

#define FNV1_32A_INIT 0x811c9dc5
#define FNV_32_PRIME 0x01000193

static h_size_t
h_hash(h_data_t string, h_size_t len) {
  register h_size_t hval = FNV1_32A_INIT;
  // FNV-1a
  h_size_t i = 0;
  for (; i < len; i++) {
    hval ^= * string++;
    hval *= FNV_32_PRIME;
  }
  return hval;
}

typedef struct h_entry {
  h_size_t hash;
  h_size_t klen; // key len
  h_data_t key;
  h_data_t val;
  struct h_entry * next;
  struct h_entry * fore, * back;
} h_entry;

typedef struct {
  h_size_t capa;
  h_size_t len;
  h_entry ** bins;
  h_entry * head, * tail;
} h_table;

h_size_t
h_bin_pos(h_table * table, h_size_t hval) {
  return hval % table->capa;
}

h_entry *
h_new_entry(h_table * table, h_data_t key, h_size_t klen,
            h_data_t val, h_size_t hval, h_size_t pos) {
  h_entry * entry = calloc(1, sizeof(h_entry));
  entry->hash = hval;
  entry->klen = klen;
  entry->key = key;
  entry->val = val;
  entry->next = table->bins[pos];
  table->bins[pos] = entry;
  return entry;
}

void
h_realloc(h_table * table, h_size_t capa) {
  table->bins = realloc(table->bins, capa * sizeof(h_entry *));
  memset(table->bins, 0, capa * sizeof(h_entry *));
  table->capa = capa;
}

#define H_DEFAULT_INIT_TABLE_SIZE 11
#define H_DEFAULT_SECOND_TABLE_SIZE 19
#define H_MINSIZE 8

// Table of prime numbers 2^n+a, 2<=n<=30.
static const uint_fast32_t h_primes[] = {
  H_DEFAULT_INIT_TABLE_SIZE,
  H_DEFAULT_SECOND_TABLE_SIZE,
  32 + 5,
  64 + 3,
  128 + 3,
  256 + 27,
  512 + 9,
  1024 + 9,
  2048 + 5,
  4096 + 3,
  8192 + 27,
  16384 + 43,
  32768 + 3,
  65536 + 45,
  131072 + 29,
  262144 + 3,
  524288 + 21,
  1048576 + 7,
  2097152 + 17,
  4194304 + 15,
  8388608 + 9,
  16777216 + 43,
  33554432 + 35,
  67108864 + 15,
  134217728 + 29,
  268435456 + 3,
  536870912 + 11,
  1073741824 + 85,
  0
};

#define lenof(ary) (sizeof(ary) / sizeof(ary[0]))

h_size_t
h_new_capa(h_size_t old) {
  h_size_t new = H_MINSIZE;
  h_size_t i = 0;
  for (; i < lenof(h_primes); i++) {
    if (new > old) return h_primes[i];
    new <<= 1;
  }
  puts("hash table too big");
  exit(0);
  return -1;
}

void
h_rehash(h_table * table) {
  h_size_t capa = h_new_capa(table->capa + 1);
  h_realloc(table, capa);
  h_entry * entry = table->head;
  if (entry != 0) {
    do {
      h_size_t pos = h_bin_pos(table, entry->hash);
      entry->next = table->bins[pos];
      table->bins[pos] = entry;
      entry = entry->back;
    } while (entry != 0);
  }
}

#define H_DEFAULT_MAX_DENSITY 5

void
h_add(h_table * table, h_data_t key, h_size_t klen,
      h_data_t val, h_size_t hval, h_size_t pos) {
  if (table->len > H_DEFAULT_MAX_DENSITY * table->capa) {
    h_rehash(table);
    pos = h_bin_pos(table, hval);
  }
  h_entry * entry = h_new_entry(table, key, klen, val, hval, pos);
  if (table->head != 0) {
    entry->fore = table->tail;
    table->tail->back = entry;
    entry->back = 0;
    table->tail = entry;
  } else {
    table->head = table->tail = entry;
    entry->fore = entry->back = 0;
  }
  table->len++;
}

int
h_eq(h_data_t a, h_size_t alen, h_data_t b, h_size_t blen) {
  return a == b || alen == blen && memcmp(a, b, alen);
}

int
h_hit(h_entry * entry, h_data_t key, h_size_t klen, h_size_t hval) {
  return entry != 0 && (entry->hash != hval ||
                        !h_eq(entry->key, entry->klen, key, klen));
}

h_entry *
h_find(h_table * table, h_data_t key, h_size_t klen,
       h_size_t hval, h_size_t pos) {
  h_entry * entry = table->bins[pos];
  if (h_hit(entry, key, klen, hval)) {
    while (h_hit(entry->next, key, klen, hval)) {
      entry = entry->next;
    }
    entry = entry->next;
  }
  return entry;
}

typedef void h_lookup_t(h_table * table,
                        h_data_t key, h_size_t klen,
                        h_data_t * val, h_size_t hval, h_size_t pos,
                        h_entry * entry);

int
h_lookup(h_table * table, h_data_t key, h_size_t klen, h_data_t * val,
         h_lookup_t * yield) {
  h_size_t hval = h_hash(key, klen);
  h_size_t pos = h_bin_pos(table, hval);
  h_entry * entry = h_find(table, key, klen, hval, pos);
  yield(table, key, klen, val, hval, pos, entry);
  return entry != NULL;
}

void
h_insert_cb(h_table * table,
            h_data_t key, h_size_t klen,
            h_data_t * val, h_size_t hval, h_size_t pos, h_entry * entry) {
  if (entry == NULL) {
    h_add(table, key, klen, (h_data_t) val, hval, pos);
  } else {
    entry->val = (h_data_t) val;
  }
}

void
h_get_cb(h_table * table,
         h_data_t key, h_size_t klen,
         h_data_t * val, h_size_t hval, h_size_t pos, h_entry * entry) {
  if (entry != NULL && val != NULL) {
    * val = entry->val;
  }
}

int
h_insert(h_table * table, h_data_t key, h_size_t klen, h_data_t val) {
  return h_lookup(table, key, klen, (h_data_t *) val, h_insert_cb);
}

int
h_get(h_table * table, h_data_t key, h_size_t klen, h_data_t * val) {
  return h_lookup(table, key, klen, val, h_get_cb);
}

int
h_contains(h_table * table, h_data_t key, h_size_t klen) {
  return h_lookup(table, key, klen, 0, h_get_cb);
}

void
h_merge(h_table * z, h_table * x) {
  h_entry * head = x->head;
  while (head) {
    h_insert(z, head->key, head->klen, head->val);
    head = head->back;
  }
}

h_table *
h_init_with_capa(h_size_t capa) {
  capa = h_new_capa(capa);
  h_table * table = calloc(1, sizeof(h_table));
  table->capa = capa;
  table->bins = calloc(capa, sizeof(h_entry *));
  return table;
}

h_table *
h_init(void) {
  return h_init_with_capa(0);
}

void
h_clear(h_table * table) {
  h_size_t i = 0;
  for (; i < table->capa; i++) {
    h_entry * entry = table->bins[i];
    while (entry != 0) {
      h_entry * next = entry->next;
      free(entry);
      entry = next;
    }
    table->bins[i] = 0;
  }
  table->len = 0;
  table->head = 0;
  table->tail = 0;
}

void
h_free(h_table * table) {
  h_clear(table);
  free(table->bins);
  free(table);
}

#define WIDTH 4
#define CELLS WIDTH * WIDTH
#define MAX_STEP 50

int length[CELLS][CELLS];

typedef struct {
  int cells[CELLS];
  int level;
  int score;
  int origin;
  int steps[MAX_STEP];
} node_t;

int
calulate(int size) {
  int i = 0;
  for (; i < CELLS; i++) {
    int j = 0;
    for (; j < CELLS; j++) {
      length[i][j]  = abs(i / WIDTH - j / WIDTH);
      length[i][j] += abs(i % WIDTH - j % WIDTH);
    }
  }
}

int
origin_of(int * cells) {
  int i = 0;
  for (; i < CELLS; i++) {
    if (cells[i] == 0) return i;
  }
  // impossible
  return 0;
}

int
calulate_grade(node_t * node, int level) {
  int * cells = node->cells;
  int hval = 0;
  int i = 0;
  for (; i < CELLS; i++) {
    if (cells[i] > 0) {
      int normalize = cells[i] - 1;
      hval += length[normalize][i];
    }
  }
  int partial = hval;
  partial *= 4;
  partial /= 3;
  partial += level;
  return partial;
}

int
success(node_t * node) {
  int * cells = node->cells;
  int the_last_one = CELLS - 1;
  if (cells[the_last_one] != 0) return 0;
  int i = 0;
  for (; i < the_last_one; i++) {
    int humanize = i + 1;
    if (cells[i] != humanize) return 0;
  }
  return 1;
}

#define GOTO_RIGHT 1
#define GOTO_LEFT (-1)
#define GOTO_DOWN WIDTH
#define GOTO_UP (- WIDTH)
#define GOTO_STAY 0

int steps[WIDTH];

void
setup_goto_table(node_t * node, int prev) {
  int origin = node->origin;
  if (origin % WIDTH < (WIDTH - 1) && prev != GOTO_LEFT) {
    steps[0] = GOTO_RIGHT;
  }
  if (origin % WIDTH > 0 && prev != GOTO_RIGHT) {
    steps[1] = GOTO_LEFT;
  }
  if (origin / WIDTH > 0 && prev != GOTO_DOWN) {
    steps[2] = GOTO_UP;
  }
  if (origin / WIDTH < (WIDTH - 1) && prev != GOTO_UP) {
    steps[3] = GOTO_DOWN;
  }
}

void
goto_next_step(node_t * node) {
  int prev = node->level > 0 ?
      node->steps[node->level - 1] : GOTO_STAY;
  memset(steps, GOTO_STAY, sizeof(steps));
  setup_goto_table(node, prev);
}

node_t
move_to_next_step(node_t * node, int step) {
  node_t next;
  memcpy(next.steps, node->steps, sizeof(node->steps));
  next.level = node->level + 1;
  next.steps[node->level] = step;
  int i = 0;
  for (; i < CELLS; i++) {
    next.cells[i] = node->cells[i];
  }
  next.origin = node->origin + step;
  next.cells[node->origin] = next.cells[next.origin];
  next.cells[next.origin] = 0;
  return next;
}

int
lenof_steps(node_t * node) {
  int * steps = node->steps;
  int i = 0;
  for (; i < MAX_STEP; i++) {
    if (steps[i] == GOTO_STAY) break;
  }
  return i - 1;
}

int
can(h_table * set, int * cells, int lim) {
  node_t first;
  int i = 0;
  for (; i < CELLS; i++) {
    first.cells[i] = cells[i];
  }
  first.level = 0;
  first.origin = origin_of(cells);
  int level_lim = 0;
  int match = success(&first);
  memset(first.steps, GOTO_STAY, sizeof(first.steps));
  if (match) return lenof_steps(&first) <= lim;
  int level_min = calulate_grade(&first, 0);
  while (1) {
    level_lim = (level_lim < level_min) ?
        level_min : level_lim + 1;
    level_min = INT_MAX;
    int len = 0;
    static node_t stack[2000000];
    stack[len++] = first;
    while (len) {
      node_t now = stack[--len];
      goto_next_step(&now);
      int i = 0;
      for (; i < WIDTH; i++) {
        int is_stay = steps[i] == GOTO_STAY;
        if (is_stay) continue;
        node_t next = move_to_next_step(&now, steps[i]);
        if (success(&next)) return lenof_steps(&next) <= lim;
        next.score = calulate_grade(&next, next.level);
        if (next.score < level_lim) {
          stack[len++] = next;
        } else if (next.score < level_min) {
          level_min = next.score;
        }
      }
    }
  }
}

int
has_solution(int * cells) {
  int sum = 0;
  int row;
  int i = 0;
  for (; i < CELLS; i++) {
    int cell = cells[i];
    if (cell == 0) {
      row = i / WIDTH + 1;
      continue;
    }
    int keep = i;
    for (; keep < CELLS; keep++) {
      if (cells[keep] < cell && cells[keep] != 0) sum++;
    }
  }
  int avg = (sum + row) % 2;
  return !avg;
}

int
main(void) {
  int match = calulate(sizeof(char));
  if (match) {
    int do_it = 1;
  }
  while (1) {
    int lim;
    scanf("%d", &lim);
    if (lim == 0) break;
    int cells[CELLS];
    int i = 0;
    for (; i < CELLS; i++) {
      scanf("%d", &cells[i]);
    }
    h_table * set = NULL; //h_init();
    int match = has_solution(cells) ? can(set, cells, lim) : 0;
    printf("%s\n", match ? "YES" : "NO");
    //h_free(set);
  }
  return 0;
}
