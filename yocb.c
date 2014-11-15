#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
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
                        h_eq(entry->key, entry->klen, key, klen));
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


//                                  0zzz zzzz
//                                   000 0000 (     0) to
//                                   111 1111 (    7F)
//                       110y yyyy  10zz zzzz
//                          0 0010    00 0000 (    80) to
//                          1 1111    11 1111 (   7FF)
//            1110 xxxx  10yy yyyy  10zz zzzz
//                 0000    10 0000    00 0000 (   800) to
//                 0000    11 1111    11 1111 (   FFF)
//                 0001    00 0000    00 0000 (  1000) to
//                 1100    11 1111    11 1111 (  CFFF)
//                 1101    00 0000    00 0000 (  D000) to
//                 1101    01 1111    11 1111 (  D7FF)
//                 1110    00 0000    00 0000 (  E000) to
//                 1111    11 1111    11 1111 (  FFFF)
// 1111 0www  10xx xxxx  10yy yyyy  10zz zzzz
//       000    01 0000    00 0000    00 0000 ( 10000) to
//       000    11 1111    11 1111    11 1111 ( 1FFFF)
//       001    00 0000    00 0000    00 0000 ( 20000) to
//       011    11 1111    11 1111    11 1111 ( FFFFF)
//       100    00 0000    00 0000    00 0000 (100000) to
//       100    00 1111    11 1111    11 1111 (10FFFF)
//
// transition digram(state 0 to 7):
//                               0 [00-7F] (     0 to     7F)
//                     0 [C2-DF] 1 [80-BF] (    80 to    7FF)
//           0  E0     2 [A0-BF] 1 [80-BF] (   800 to    FFF)
//           0 [E1-EC] 3 [80-BF] 1 [80-BF] (  1000 to   CFFF)
//           0  ED     4 [80-9F] 1 [80-BF] (  D000 to   D7FF)
//           0 [EE-EF] 3 [80-BF] 1 [80-BF] (  E000 to   FFFF)
// 0  F0     5 [90-BF] 3 [80-BF] 1 [80-BF] ( 10000 to  1FFFF)
// 0 [F1-F3] 6 [80-BF] 3 [80-BF] 1 [80-BF] ( 20000 to  FFFFF)
// 0  F4     7 [80-8F] 3 [80-BF] 1 [80-BF] (100000 to 10FFFF)

enum state {
  ACCEPT = -2, // accept
  FAILURE      // failure
};

#define A ACCEPT
#define F FAILURE

static int8_t trans[][256] = {
  { // state 0
    //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    /* 0 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
    /* 1 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
    /* 2 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
    /* 3 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
    /* 4 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
    /* 5 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
    /* 6 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
    /* 7 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
    /* 8 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 9 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* A */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* B */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* C */ F, F, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    /* D */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    /* E */ 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3,
    /* F */ 5, 6, 6, 6, 7, F, F, F, F, F, F, F, F, F, F, F
  },
  { // state 1
    //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 8 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
    /* 9 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
    /* A */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
    /* B */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
    /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
  },
  { // state 2
    //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 8 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 9 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* A */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    /* B */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
  },
  { // state 3
    //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 8 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    /* 9 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    /* A */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    /* B */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
  },
  { // state 4
    //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 8 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    /* 9 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    /* A */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* B */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
  },
  { // state 5
    //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 8 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 9 */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    /* A */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    /* B */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
  },
  { // state 6
    //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 8 */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    /* 9 */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    /* A */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    /* B */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
  },
  { // state 7
    //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* 8 */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    /* 9 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* A */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* B */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
  }
};

static size_t
utf8_len(utf_t * c) {
  size_t len = 0;
  size_t state = 0;
  while (1) {
    state = trans[state][* c];
    c += 1;
    len += 1;
    switch (state) {
      case ACCEPT:
        return len;
      case FAILURE:
        return 0;
    }
  };
}

typedef uint32_t ucode_t;

#define BIT_MASK(n) ((1 << (n)) - 1)

static ucode_t
utf8_code(utf_t * c) {
  ucode_t code = * c;
  size_t len = utf8_len(c);
  if (len > 1) {
    len--;
    code &= BIT_MASK(6 - len);
    while (len--) {
      c++;
      code <<= 6;
      code |= * c & BIT_MASK(6);
    }
  }
  return code;
}

FILE *
file_open(int files_len, utf_t * fname) {
  if (files_len != 1) {
    puts("should input 1 file");
    exit(0);
  }
  FILE * file = fopen(fname, "r");
  if (file == NULL) {
    printf("no %s file\n", fname);
    exit(0);
  }
  return file;
}

typedef void *
fread_t(utf_t * fname, utf_t * file, size_t size, void * arg);

void *
file_read(int files_len, utf_t * fname, fread_t * yield, void * arg) {
  FILE * file = file_open(files_len, fname);
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);
  utf_t * buf = malloc(size);
  if (buf == NULL) {
    printf("alloc memory error for file %s\n", fname);
    exit(0);
  }
  size_t read_size = fread(buf, 1, size, file);
  if (read_size != size) {
    printf("reading error for file %s\n", fname);
    exit(0);
  }
  fclose(file);
  void * ret = yield(fname, buf, size, arg);
  if (ret == 0) free(buf);
  return ret;
}

typedef struct {
  size_t len;
  ucode_t code;
  utf_t * c;
} uchar_t;

typedef enum {
  // T = Type
  // CSCALL = C static call

  UNKNOWN,

  CTSELF,    // 1  [middle dot]
  CCALL,     // 2  [middle dot][a-zA-Z_][a-zA-Z_1-9]*
  CTCLASS,   // 3  [middle dot][middle dot]
  CSTCALL,   // 4  [low grave accent][a-zA-Z_][a-zA-Z_1-9]
  CREQUIRE,  // 5  : require
  CCLASS,    // 6  : class
  CEND,      // 7  : end
  CTYPEDEF,  // 8  : end
  CMETHOD,   // 9  : [a-zA-Z_][a-zA-Z_1-9]*
  CDMETHOD,  //10  : [a-zA-Z_][a-zA-Z_1-9]*
  CINSTANCE, //11  @ [a-zA-Z_][a-zA-Z_1-9]*
  CSELF,     //12  self
  CSUPER,    //13  super
  CSTATIC,   //14  static
  CID,       //15  [a-zA-Z_][a-zA-Z_1-9]*
  CLPARE,    //16  (
  CRPARE,    //17  )
  CLBRACE,   //18  {
  CRBRACE,   //19  }
  CQUOTE,    //20  "
  CBSLASH,   //21  [back slash]
  CBQUOTE,   //22  [back slash]"
  CSLASH,    //23  /
  CCATLINE,  //24  /0x0A
  CMUL,      //25  *
  CCOM,      //26  //
  CCOMS_BEG, //27  /[mul]
  CCOMS_END, //28  [mul]/
  CNSIGN,    //29  #
  CDECLEND,  //30  ;
  CSPACE,    //31  [space]
  CTERM,     //32  0x0A
  CSUCALL,   //33  super call, eg. super(), used in parsing, not scan,
  CSUMCALL,  //34  super method call, eg. super[middle dot]foo()
  CSEMCALL,  //35  self method call, eg. [middle dot]foo()
  CIDMCALL,  //36  id method call, eg. bar[middle dot]foo()
  CSTMCALL,  //37  static id method call, eg. bar[low grave accent]foo()
  CFREQUIRE, //38  require file name, eg. require "abc.c"
  CCMETHOD,  //39  class method, eg. void : abc(int x) { }
  CSUCCALL,  //40  super class call, eg. void : abc(int x) { super(x) }
  CSUCMCALL, //41  super class method call, eg.
             //      void : foo(int x) { }
             //      void : bar(int x, int y) { super[middle dot]foo(x) }

  CLASS,     //42  class
  EXTENDS,   //43  <
  LBLOCK,    //44  {
  RBLOCK,    //45  }
  STRUCT,    //46  struct
  METHODS,   //47  methods
  TERM,      //48  [\r\n\s]+

  SELF,      //49  self
  ID,        //50  [a-zA-Z_][a-zA-Z_1-9]*
  METHOD,    //51  :
  STAT,      //52  ;
  TSELF,     //53  [middle dot]
  TCLASS,    //54  [middle dot][middle dot]
  OTHERS     //55  .*
} def_t;

typedef struct {
  ucode_t cmp;
  ucode_t * period;
} dfa_t;

typedef struct {
  def_t def;
  size_t len;
  utf_t * string;
} tok_t;

typedef struct scan {
  size_t i;
  size_t size;
  utf_t * string;
  struct next * (* states)(void);
  size_t eof;
} scan_t;

int
scan_is(ucode_t code, dfa_t * dfa) {
  size_t i = 0;
  while (1) {
    dfa_t * node = &dfa[i];
    if (node->period == NULL) {
      i *= 2;
      i += (code <= node->cmp) ? 1 : 2;
    } else {
      return (code >= node->period[0] &&
              code <= node->period[1]);
    }
  }
}

uchar_t
scan_char(scan_t * scan) {
  utf_t * string = scan->string;
  size_t i = scan->i;
  size_t size = scan->size;
  if (i >= size) {
    if (scan->eof) {
      printf("read end of file %zu\n", size);
      exit(0);
    } else {
      scan->eof = 1;
    }
    return (uchar_t) {0};
  }
  utf_t * str = &string[i];
  size_t len = utf8_len(str);
  ucode_t code = utf8_code(str);
  return (uchar_t) {len, code, str};
}

typedef enum {
  START,

  CCALL1, CCALL2,
  CSTCALL1, CSTCALL2,
  CTCLASS1,
  CREQUIRE1, CREQUIRE2, CREQUIRE3, CREQUIRE4, CREQUIRE5, CREQUIRE6, CREQUIRE7,
  CCLASS1, CCLASS2, CCLASS3, CCLASS4, CCLASS5,
  CEND1, CEND2, CEND3,
  CTYPEDEF1, CTYPEDEF2, CTYPEDEF3, CTYPEDEF4, CTYPEDEF5, CTYPEDEF6, CTYPEDEF7,
  CMETHOD1, CMETHOD2,
  CINSTANCE1, CINSTANCE2,
  CSELF1, CSELF2, CSELF3, CSELF4, CSELF5,
  CSUPER1, CSUPER2, CSUPER3, CSUPER4,
  CSTATIC1, CSTATIC2, CSTATIC3, CSTATIC4, CSTATIC5,
  CID1,
  CLPARE1,
  CRPARE1,
  CLBRACE1,
  CRBRACE1,
  CQUOTE1,
  CBSLASH1, CBSLASH2,
  CSLASH1,
  CCATLINE1,
  CMUL1,
  CCOM1,
  CCOMS_BEG1,
  CCOMS_END1,
  CNSIGN1,
  CDECLEND1,
  CBQUOTE1,
  CSPACE1,
  CTERM1,

  CLASS1, CLASS2, CLASS3, CLASS4, CLASS5,
  METHODS1, METHODS2, METHODS3, METHODS4, METHODS5, METHODS6, METHODS7,
  STRUCT1, STRUCT2, STRUCT3, STRUCT4, STRUCT5, STRUCT6,
  EXTENDS1,
  LBLOCK1,
  RBLOCK1,
  ID1,
  TERM1,

  SELF1, SELF2, SELF3, SELF4,
  METHOD1,
  STAT1,
  TSELF1,
  TCLASS1,
  OTHERS1,
  STATES_LEN
} state_t;

void
scan_perror(ucode_t code) {
  printf("not allowed char %" PRIu32 "\n", code);
  exit(0);
}

// U = unicode

#define UCMP(cmp) {cmp, 0}
#define UPERIOD(begin, end) {0, (ucode_t[]) {begin, end}}

static dfa_t ccall[] = {
  UCMP('_'),

  UCMP('Z'),
  UPERIOD('a', 'z'),

  UPERIOD('A', 'Z'),
  UPERIOD('_', '_')
};

static dfa_t cdid[] = {
  UCMP('_'),

  UCMP('Z'),
  UCMP('r'),

  UCMP('9'),
  UPERIOD('_', '_'),
  UPERIOD('a', 'r'), // no [s]elf
  UPERIOD('t', 'z'),

  UPERIOD('0', '9'),
  UPERIOD('A', 'Z')
};

static dfa_t cmethod[] = {
  UCMP('d'),

  UCMP('_'),
  UCMP('s'),

  UCMP('Z'),
  UCMP('b'),
  UCMP('q'),
  UPERIOD('u', 'z'),

  UPERIOD('A', 'Z'),
  UPERIOD('_', '_'),
  UPERIOD('a', 'b'), // no [c]class
  UPERIOD('d', 'd'), // no [e]nd
  UPERIOD('f', 'q'), // no [r]equire
  UPERIOD('s', 's')  // no [t]ypedef
};

static dfa_t did_head[] = {
  UCMP('l'),

  UCMP('_'),
  UCMP('r'),

  UCMP('Z'),
  UCMP('b'),
  UPERIOD('n', 'r'), // no [s]truct
  UPERIOD('t', 'z'),

  UPERIOD('A', 'Z'),
  UPERIOD('_', '_'),
  UPERIOD('a', 'b'), // no [c]lass
  UPERIOD('d', 'l')  // no [m]ethods
};

static dfa_t did_tail[] = {
  UCMP('Z'),

  UCMP('9'),
  UCMP('_'),

  UPERIOD('0', '9'),
  UPERIOD('A', 'Z'),
  UPERIOD('_', '_'),
  UPERIOD('a', 'z')
};

#define UNOT(code) { \
    UCMP('_'), \
    \
    UCMP('Z'), \
    UCMP(code - 1), \
    \
    UCMP('9'), \
    UPERIOD('_', '_'), \
    UPERIOD('a', code - 1), \
    UPERIOD(code + 1, 'z'), \
    \
    UPERIOD('0', '9'), \
    UPERIOD('A', 'Z') \
  }

static dfa_t dnot_l[] = UNOT('l');
static dfa_t dnot_a[] = UNOT('a');
static dfa_t dnot_s[] = UNOT('s');
static dfa_t dnot_e[] = UNOT('e');
static dfa_t dnot_t[] = UNOT('t');
static dfa_t dnot_h[] = UNOT('h');
static dfa_t dnot_o[] = UNOT('o');
static dfa_t dnot_d[] = UNOT('d');
static dfa_t dnot_r[] = UNOT('r');
static dfa_t dnot_u[] = UNOT('u');
static dfa_t dnot_c[] = UNOT('c');

static dfa_t dnot_n[] = UNOT('n');
static dfa_t dcself1[] = {
  UCMP('d'),

  UCMP('Z'),
  UCMP('t'),

  UCMP('9'),
  UCMP('_'),
  UPERIOD('f', 's'), // no s[t]atic, s[u]per
  UPERIOD('v', 'z'),

  UPERIOD('0', '9'),
  UPERIOD('A', 'Z'),
  UPERIOD('_', '_'),
  UPERIOD('a', 'd')  // no s[e]lf
};
static dfa_t dnot_f[] = UNOT('f');
static dfa_t dnot_p[] = UNOT('p');
static dfa_t dnot_q[] = UNOT('q');
static dfa_t dnot_i[] = UNOT('i');
static dfa_t dnot_y[] = UNOT('y');

static dfa_t dterm1[] = {
  UCMP(0x0D),

  UCMP(0x0A),
  UPERIOD(0x20, 0x20),

  UPERIOD(0x0A, 0x0A),
  UPERIOD(0x0D, 0x0D)
};

typedef struct {
  dfa_t * code;
  state_t next;
} scmp_t; // state compare

typedef struct next {
  scmp_t * to;
  def_t def;
  state_t last;
} next_t; // next state

#define UCHAR(c) (dfa_t[]) UPERIOD(c, c)
#define NEXT_STATE(code, next) {code, next}
#define NEXT_CHAR(c, next) NEXT_STATE(UCHAR(c), next)
#define NEXT_1CHAR(c, state) \
  (scmp_t[]) {NEXT_CHAR(c, state), 0}
#define NEXT_1STATE(code, state) \
  (scmp_t[]) {NEXT_STATE(code, state), 0}
#define FINISHED_CHAR(def) (next_t) {0, def, 0}
#define FINISHED_STATE(def) def, 0
#define GOTO_STATE(state) UNKNOWN, state

#define NEXT_KEYWORD(c, next, not, id) (next_t) { \
    (scmp_t[]) { \
      NEXT_CHAR(c, next), \
      NEXT_STATE(not, id), 0 \
    }, OTHERS, 0 \
  }
#define NEXT_CHAR_END(def, id) (next_t) { \
    (scmp_t[]) { \
      NEXT_STATE(did_tail, id), 0 \
    }, def, 0 \
  }

// CKEYWORD = C keyword
// CMKEYWORD = C method keyword
// NKEYWORD = not C keyword
#define NEXT_CKEYWORD(c, next, not) \
  NEXT_KEYWORD(c, next, not, CID1)
#define NEXT_CMKEYWORD(c, next, not) \
  NEXT_KEYWORD(c, next, not, CMETHOD2)
#define NEXT_NKEYWORD(c, next, not) \
  NEXT_KEYWORD(c, next, not, ID1)
#define NEXT_CCHAR_END(def) \
  NEXT_CHAR_END(def, CID1)
#define NEXT_NCHAR_END(def) \
  NEXT_CHAR_END(def, ID1)

#define NEXT_CMETHOD(def) (next_t) { \
    (scmp_t[]) { \
      NEXT_STATE(did_tail, CMETHOD2), 0 \
    }, def, 0 \
  }

#define MIDDLE_DOT 0xB7
#define LOW_GRAVE_ACCENT 0x02CE

static next_t cstate_cstart = {
  (scmp_t[]) {
    NEXT_STATE(cdid, CID1),
    NEXT_CHAR(':', CMETHOD1),
    NEXT_CHAR('@', CINSTANCE1),
    NEXT_CHAR('s', CSELF1),
    NEXT_CHAR('(', CLPARE1),
    NEXT_CHAR(')', CRPARE1),
    NEXT_CHAR('{', CLBRACE1),
    NEXT_CHAR('}', CRBRACE1),
    NEXT_CHAR('"', CQUOTE1),
    NEXT_CHAR('\\', CBSLASH1),
    NEXT_CHAR('/', CSLASH1),
    NEXT_CHAR('*', CMUL1),
    NEXT_CHAR('#', CNSIGN1),
    NEXT_CHAR(';', CDECLEND1),
    NEXT_CHAR(' ', CSPACE1),
    NEXT_CHAR(0x0A, CTERM1),
    NEXT_CHAR(MIDDLE_DOT, CCALL1),
    NEXT_CHAR(LOW_GRAVE_ACCENT, CSTCALL1), 0
  },
  GOTO_STATE(OTHERS1)
};
static next_t cstate_ccall1 = {
  (scmp_t[]) {
    NEXT_CHAR(MIDDLE_DOT, CTCLASS1),
    NEXT_STATE(ccall, CCALL2), 0
  },
  FINISHED_STATE(CTSELF)
};
static next_t cstate_ctclass = FINISHED_CHAR(CTCLASS);
static next_t cstate_ccall2 = {
  NEXT_1STATE(did_tail, CCALL2),
  FINISHED_STATE(CCALL)
};
static next_t cstate_cstcall1 = {
  NEXT_1STATE(ccall, CSTCALL2),
  FINISHED_STATE(OTHERS)
};
static next_t cstate_cstcall2 = {
  NEXT_1STATE(did_tail, CSTCALL2),
  FINISHED_STATE(CSTCALL)
};
static next_t cstate_cmethod1 = {
  (scmp_t[]) {
    NEXT_CHAR('r', CREQUIRE1),
    NEXT_CHAR('c', CCLASS1),
    NEXT_CHAR('e', CEND1),
    NEXT_CHAR('t', CTYPEDEF1),
    NEXT_STATE(cmethod, CMETHOD2), 0
  },
  FINISHED_STATE(OTHERS)
};
static next_t cstate_cmethod2 = {
  NEXT_1STATE(did_tail, CMETHOD2),
  FINISHED_STATE(CMETHOD)
};
static next_t cstate_crequire[] = {
  NEXT_CMKEYWORD('e', CREQUIRE2, dnot_e),
  NEXT_CMKEYWORD('q', CREQUIRE3, dnot_q),
  NEXT_CMKEYWORD('u', CREQUIRE4, dnot_u),
  NEXT_CMKEYWORD('i', CREQUIRE5, dnot_i),
  NEXT_CMKEYWORD('r', CREQUIRE6, dnot_r),
  NEXT_CMKEYWORD('e', CREQUIRE7, dnot_e),
  NEXT_CMETHOD(CREQUIRE)
};
static next_t cstate_cclass[] = {
  NEXT_CMKEYWORD('l', CCLASS2, dnot_l),
  NEXT_CMKEYWORD('a', CCLASS3, dnot_a),
  NEXT_CMKEYWORD('s', CCLASS4, dnot_s),
  NEXT_CMKEYWORD('s', CCLASS5, dnot_s),
  NEXT_CMETHOD(CCLASS)
};
static next_t cstate_cend[] = {
  NEXT_CMKEYWORD('n', CEND2, dnot_n),
  NEXT_CMKEYWORD('d', CEND3, dnot_d),
  NEXT_CMETHOD(CEND)
};
static next_t cstate_ctypedef[] = {
  NEXT_CMKEYWORD('y', CTYPEDEF2, dnot_y),
  NEXT_CMKEYWORD('p', CTYPEDEF3, dnot_p),
  NEXT_CMKEYWORD('e', CTYPEDEF4, dnot_e),
  NEXT_CMKEYWORD('d', CTYPEDEF5, dnot_d),
  NEXT_CMKEYWORD('e', CTYPEDEF6, dnot_e),
  NEXT_CMKEYWORD('f', CTYPEDEF7, dnot_f),
  NEXT_CMETHOD(CTYPEDEF)
};
static next_t cstate_cinstance1 = {
  NEXT_1STATE(ccall, CINSTANCE2),
  FINISHED_STATE(OTHERS)
};
static next_t cstate_cinstance2 = {
  NEXT_1STATE(did_tail, CINSTANCE2),
  FINISHED_STATE(CINSTANCE)
};
static next_t cstate_cself1 = {
  (scmp_t[]) {
    NEXT_STATE(dcself1, CID1),
    NEXT_CHAR('e', CSELF2),
    NEXT_CHAR('t', CSTATIC1),
    NEXT_CHAR('u', CSUPER1), 0
  },
  FINISHED_STATE(OTHERS)
};
static next_t cstate_cself2[] = {
  NEXT_CKEYWORD('l', CSELF3, dnot_l),
  NEXT_CKEYWORD('f', CSELF4, dnot_f),
  NEXT_CCHAR_END(CSELF)
};
static next_t cstate_cstatic[] = {
  NEXT_CKEYWORD('a', CSTATIC2, dnot_a),
  NEXT_CKEYWORD('t', CSTATIC3, dnot_t),
  NEXT_CKEYWORD('i', CSTATIC4, dnot_i),
  NEXT_CKEYWORD('c', CSTATIC5, dnot_c),
  NEXT_CCHAR_END(CSTATIC)
};
static next_t cstate_csuper[] = {
  NEXT_CKEYWORD('p', CSUPER2, dnot_p),
  NEXT_CKEYWORD('e', CSUPER3, dnot_e),
  NEXT_CKEYWORD('r', CSUPER4, dnot_r),
  NEXT_CCHAR_END(CSUPER)
};
static next_t cstate_cid = {
  NEXT_1STATE(did_tail, CID1),
  FINISHED_STATE(CID)
};
static next_t cstate_clpare = FINISHED_CHAR(CLPARE);
static next_t cstate_crpare = FINISHED_CHAR(CRPARE);
static next_t cstate_clbrace = FINISHED_CHAR(CLBRACE);
static next_t cstate_crbrace = FINISHED_CHAR(CRBRACE);
static next_t cstate_cquote = FINISHED_CHAR(CQUOTE);
static next_t cstate_cbslash1 = {
  (scmp_t[]) {
    NEXT_CHAR('"', CBSLASH2),
    NEXT_CHAR(0x0A, CCATLINE1), 0
  },
  FINISHED_STATE(CBSLASH)
};
static next_t cstate_cbslash2 = FINISHED_CHAR(CBQUOTE);
static next_t cstate_ccatline1 = FINISHED_CHAR(CCATLINE);
static next_t cstate_cslash1 = {
  (scmp_t[]) {
    NEXT_CHAR('/', CCOM1),
    NEXT_CHAR('*', CCOMS_BEG1), 0
  },
  FINISHED_STATE(CSLASH)
};
static next_t cstate_ccom = FINISHED_CHAR(CCOM);
static next_t cstate_ccoms_beg = FINISHED_CHAR(CCOMS_BEG);
static next_t cstate_cmul = {
  NEXT_1CHAR('/', CCOMS_END1),
  FINISHED_STATE(CMUL)
};
static next_t cstate_ccoms_end = FINISHED_CHAR(CCOMS_END);
static next_t cstate_cnsign = FINISHED_CHAR(CNSIGN);
static next_t cstate_cdeclend = FINISHED_CHAR(CDECLEND);
static next_t cstate_cspace = FINISHED_CHAR(CSPACE);
static next_t cstate_cterm = FINISHED_CHAR(CTERM);
static next_t cstate_cothers = FINISHED_CHAR(OTHERS);

next_t *
cscan_states(void) {
  static int done = 0;
  static next_t states[STATES_LEN] = {0};
  if (done) return states;
  states[START] = cstate_cstart;
  states[CCALL1] = cstate_ccall1;
  states[CTCLASS1] = cstate_ctclass;
  states[CCALL2] = cstate_ccall2;
  states[CSTCALL1] = cstate_cstcall1;
  states[CSTCALL2] = cstate_cstcall2;
  states[CMETHOD1] = cstate_cmethod1;
  states[CMETHOD2] = cstate_cmethod2;
  states[CREQUIRE1] = cstate_crequire[0];
  states[CREQUIRE2] = cstate_crequire[1];
  states[CREQUIRE3] = cstate_crequire[2];
  states[CREQUIRE4] = cstate_crequire[3];
  states[CREQUIRE5] = cstate_crequire[4];
  states[CREQUIRE6] = cstate_crequire[5];
  states[CREQUIRE7] = cstate_crequire[6];
  states[CCLASS1] = cstate_cclass[0];
  states[CCLASS2] = cstate_cclass[1];
  states[CCLASS3] = cstate_cclass[2];
  states[CCLASS4] = cstate_cclass[3];
  states[CCLASS5] = cstate_cclass[4];
  states[CEND1] = cstate_cend[0];
  states[CEND2] = cstate_cend[1];
  states[CEND3] = cstate_cend[2];
  states[CTYPEDEF1] = cstate_ctypedef[0];
  states[CTYPEDEF2] = cstate_ctypedef[1];
  states[CTYPEDEF3] = cstate_ctypedef[2];
  states[CTYPEDEF4] = cstate_ctypedef[3];
  states[CTYPEDEF5] = cstate_ctypedef[4];
  states[CTYPEDEF6] = cstate_ctypedef[5];
  states[CTYPEDEF7] = cstate_ctypedef[6];
  states[CINSTANCE1] = cstate_cinstance1;
  states[CINSTANCE2] = cstate_cinstance2;
  states[CSELF1] = cstate_cself1;
  states[CSELF2] = cstate_cself2[0];
  states[CSELF3] = cstate_cself2[1];
  states[CSELF4] = cstate_cself2[2];
  states[CSTATIC1] = cstate_cstatic[0];
  states[CSTATIC2] = cstate_cstatic[1];
  states[CSTATIC3] = cstate_cstatic[2];
  states[CSTATIC4] = cstate_cstatic[3];
  states[CSTATIC5] = cstate_cstatic[4];
  states[CSUPER1] = cstate_csuper[0];
  states[CSUPER2] = cstate_csuper[1];
  states[CSUPER3] = cstate_csuper[2];
  states[CSUPER4] = cstate_csuper[3];
  states[CID1] = cstate_cid;
  states[CLPARE1] = cstate_clpare;
  states[CRPARE1] = cstate_crpare;
  states[CLBRACE1] = cstate_clbrace;
  states[CRBRACE1] = cstate_crbrace;
  states[CQUOTE1] = cstate_cquote;
  states[CBSLASH1] = cstate_cbslash1;
  states[CBSLASH2] = cstate_cbslash2;
  states[CCATLINE1] = cstate_ccatline1;
  states[CSLASH1] = cstate_cslash1;
  states[CCOM1] = cstate_ccom;
  states[CCOMS_BEG1] = cstate_ccoms_beg;
  states[CMUL1] = cstate_cmul;
  states[CCOMS_END1] = cstate_ccoms_end;
  states[CNSIGN1] = cstate_cnsign;
  states[CDECLEND1] = cstate_cdeclend;
  states[CSPACE1] = cstate_cspace;
  states[CTERM1] = cstate_cterm;
  states[OTHERS1] = cstate_cothers;
  done = 1;
  return states;
}

void
scan_debug(utf_t * string, size_t len) {
  return;
  utf_t buf[64];
  size_t buflen = len;
  if (buflen >= lenof(buf)) buflen = lenof(buf) - 1;
  memcpy(buf, string, buflen);
  buf[buflen] = '\0';
  printf("[%s]", buf);
}

static next_t state_start = {
  (scmp_t[]) {
    NEXT_STATE(did_head, ID1),
    NEXT_STATE(dterm1, TERM1),
    NEXT_CHAR('c', CLASS1),
    NEXT_CHAR('m', METHODS1),
    NEXT_CHAR('s', STRUCT1),
    NEXT_CHAR('<', EXTENDS1),
    NEXT_CHAR('{', LBLOCK1),
    NEXT_CHAR('}', RBLOCK1), 0
  },
  FINISHED_STATE(OTHERS)
};
static next_t state_class[] = {
  NEXT_NKEYWORD('l', CLASS2, dnot_l),
  NEXT_NKEYWORD('a', CLASS3, dnot_a),
  NEXT_NKEYWORD('s', CLASS4, dnot_s),
  NEXT_NKEYWORD('s', CLASS5, dnot_s),
  NEXT_NCHAR_END(CLASS)
};
static next_t state_struct[] = {
  NEXT_NKEYWORD('t', STRUCT2, dnot_t),
  NEXT_NKEYWORD('r', STRUCT3, dnot_r),
  NEXT_NKEYWORD('u', STRUCT4, dnot_u),
  NEXT_NKEYWORD('c', STRUCT5, dnot_c),
  NEXT_NKEYWORD('t', STRUCT6, dnot_t),
  NEXT_NCHAR_END(STRUCT)
};
static next_t state_methods[] = {
  NEXT_NKEYWORD('e', METHODS2, dnot_e),
  NEXT_NKEYWORD('t', METHODS3, dnot_t),
  NEXT_NKEYWORD('h', METHODS4, dnot_h),
  NEXT_NKEYWORD('o', METHODS5, dnot_o),
  NEXT_NKEYWORD('d', METHODS6, dnot_d),
  NEXT_NKEYWORD('s', METHODS7, dnot_s),
  NEXT_NCHAR_END(METHODS)
};
static next_t state_extends = FINISHED_CHAR(EXTENDS);
static next_t state_lblock = FINISHED_CHAR(LBLOCK);
static next_t state_rblock = FINISHED_CHAR(RBLOCK);
static next_t state_term = {
  NEXT_1STATE(dterm1, TERM1),
  FINISHED_STATE(TERM)
};
static next_t state_id = {
  NEXT_1STATE(did_tail, ID1),
  FINISHED_STATE(ID)
};
static next_t state_others = FINISHED_CHAR(OTHERS);

next_t *
scan_states(void) {
  static int done = 0;
  static next_t states[STATES_LEN] = {0};
  if (done) return states;
  states[START] = state_start;
  states[CLASS1] = state_class[0];
  states[CLASS2] = state_class[1];
  states[CLASS3] = state_class[2];
  states[CLASS4] = state_class[3];
  states[CLASS5] = state_class[4];
  states[STRUCT1] = state_struct[0];
  states[STRUCT2] = state_struct[1];
  states[STRUCT3] = state_struct[2];
  states[STRUCT4] = state_struct[3];
  states[STRUCT5] = state_struct[4];
  states[STRUCT6] = state_struct[5];
  states[METHODS1] = state_methods[0];
  states[METHODS2] = state_methods[1];
  states[METHODS3] = state_methods[2];
  states[METHODS4] = state_methods[3];
  states[METHODS5] = state_methods[4];
  states[METHODS6] = state_methods[5];
  states[METHODS7] = state_methods[6];
  states[EXTENDS1] = state_extends;
  states[LBLOCK1] = state_lblock;
  states[RBLOCK1] = state_rblock;
  states[TERM1] = state_term;
  states[ID1] = state_id;
  states[OTHERS1] = state_others;
  done = 1;
  return states;
}

#undef NEXT_CKEYWORD
#define NEXT_CKEYWORD(c, next) (next_t) { \
    (scmp_t[]) {NEXT_CHAR(c, next), 0}, \
    OTHERS, 0 \
  }
#undef NEXT_CCHAR_END
#define NEXT_CCHAR_END(def) (next_t) { \
    0, def, 0 \
  }

static next_t cstate_start = {
  (scmp_t[]) {
    NEXT_STATE(dterm1, TERM1),
    NEXT_CHAR('s', SELF1),
    NEXT_CHAR('{', LBLOCK1),
    NEXT_CHAR('}', RBLOCK1),
    NEXT_CHAR(';', STAT1),
    NEXT_CHAR('-', METHOD1),
    NEXT_CHAR(MIDDLE_DOT, TSELF1), 0
  },
  GOTO_STATE(OTHERS1)
};
static next_t cstate_self[] = {
  NEXT_CKEYWORD('e', SELF2),
  NEXT_CKEYWORD('l', SELF3),
  NEXT_CKEYWORD('f', SELF4),
  NEXT_CCHAR_END(SELF)
};
static next_t cstate_lblock = NEXT_CCHAR_END(LBLOCK);
static next_t cstate_rblock = NEXT_CCHAR_END(RBLOCK);
static next_t cstate_stat = NEXT_CCHAR_END(STAT);
static next_t cstate_tself = {
  NEXT_1CHAR(MIDDLE_DOT, TCLASS1),
  FINISHED_STATE(TSELF)
};
static next_t cstate_method = {
  NEXT_1STATE(did_tail, METHOD1),
  FINISHED_STATE(METHOD)
};
static next_t cstate_tclass = NEXT_CCHAR_END(TCLASS);
static next_t cstate_term = {
  NEXT_1STATE(dterm1, TERM1),
  FINISHED_STATE(TERM)
};
static next_t cstate_others = NEXT_CCHAR_END(OTHERS);

next_t *
scan_cstates(void) {
  static int done = 0;
  static next_t states[STATES_LEN] = {0};
  if (done) return states;
  states[START] = cstate_start;
  states[SELF1] = cstate_self[0];
  states[SELF2] = cstate_self[1];
  states[SELF3] = cstate_self[2];
  states[SELF4] = cstate_self[3];
  states[LBLOCK1] = cstate_lblock;
  states[RBLOCK1] = cstate_rblock;
  states[STAT1] = cstate_stat;
  states[TSELF1] = cstate_tself;
  states[METHOD1] = cstate_method;
  states[TCLASS1] = cstate_tclass;
  states[TERM1] = cstate_term;
  states[OTHERS1] = cstate_others;
  done = 1;
  return states;
}

tok_t
scan_token(scan_t * scan) {
  def_t def = UNKNOWN;
  state_t state = START;
  uchar_t uchar = scan_char(scan);
  next_t * states = scan->states();
  size_t i = scan->i;
  while (scan->i < scan->size) {
    ucode_t code = uchar.code;
    uint8_t match = 0;
    next_t * next = &states[state];
    scmp_t * to = next->to;
    for (; to && to->code; to++) {
      if (scan_is(code, to->code)) {
        state = to->next;
        match = 1;
        break;
      }
    }
    if (!match) {
      if (next->def == UNKNOWN) {
        state = next->last;
      } else {
        def = next->def;
        break;
      }
    }
    scan->i += uchar.len;
    uchar = scan_char(scan);
  }
  size_t len = scan->i - i;
  utf_t * string = &scan->string[i];
  scan_debug(string, len);
  return (tok_t) {def, len, string};
}

scan_t
cscan_new(utf_t * string, size_t size) {
  return (scan_t) {0, size, string, cscan_states};
}

scan_t
scan_new(utf_t * string, size_t size) {
  return (scan_t) {0, size, string, scan_states};
}

tok_t
parse_next(scan_t * scan) {
  return scan_token(scan);
}

int
parse_test(tok_t * tok, def_t def) {
  return tok->def == def;
}

void
parse_check(tok_t * tok, def_t def) {
  if (!parse_test(tok, def)) {
    printf("expected token %d, given %d\n", def, tok->def);
    exit(0);
  }
}

tok_t
parse_match(scan_t * scan, def_t def) {
  tok_t tok = parse_next(scan);
  parse_check(&tok, def);
  return tok;
}

int
parse_matchp(scan_t * scan, def_t def, tok_t * tok) {
  * tok = parse_next(scan);
  return parse_test(tok, CLPARE);
}

// match with terminator
tok_t
parse_term(scan_t * scan, def_t def) {
  tok_t tok = parse_match(scan, def);
  parse_match(scan, TERM);
  return tok;
}

typedef struct {
  size_t len;
  size_t capa;
  void * objs;
} ary_t;

typedef union {
  struct {
    ary_t name;
  } nm; // normal
  struct {
    ary_t ret;
    tok_t name;
    ary_t arg;
  } or; // override
} meth_t;

typedef struct {
  tok_t self; // union
  tok_t name; // allocated only when CMSUPER
} cal_t; // cal = call

typedef struct {
  ary_t toks;    // union
  tok_t class;   // union
  tok_t super;   // allocated only when in class block
  ary_t strukt;
  ary_t meths;
  ary_t imps;    // methods implementation
  ary_t typs;    // typedefs
  utf_t * cname; // class name
  utf_t * sname; // super name
} src_t;

typedef struct {
  utf_t * string;     // file string
  ary_t reqs;         // require
  ary_t srcs;         // sources
  h_table * classes;
  h_table * rclasses; // require classes
} cclass_t;

void
ary_new(ary_t * ary, size_t capa, size_t size) {
  if (ary->objs != 0) {
    printf("ary is already newed.\n");
    exit(0);
  }
  ary->capa = capa;
  ary->objs = calloc(capa, size);
}

void *
ary_add(ary_t * ary, void * obj, size_t size) {
  if (ary->len >= ary->capa) {
    ary->capa *= 2;
    if (ary->capa == 0) {
      ary->capa = 1;
    }
    ary->objs = realloc(ary->objs, ary->capa * size);
  }
  memcpy(ary->objs + size * ary->len++, obj, size);
  return ary->objs + size * (ary->len - 1);
}

void
ary_free(ary_t * ary) {
  free(ary->objs);
}

#define meth_new(class, capa) \
  ary_new(&(class)->meths, capa, sizeof(meth_t))

#define meth_add(class, meth) \
  ary_add(&(class)->meths, meth, sizeof(meth_t))

#define meth_get(class, i) \
  &((meth_t *) (class)->meths.objs)[i]

#define cal_get(toks, i) \
  ((cal_t **) (toks)->objs)[i]

#define tok_get(toks, i) \
  &((tok_t *) (toks)->objs)[i]

#define imp_get(toks, i) \
  ((tok_t **) (toks)->objs)[i]

#define req_get(reqs, i) \
  &((ary_t *) (reqs)->objs)[i]

#define src_get(srcs, i) \
  ((src_t **) (srcs)->objs)[i]

#define utf_get(chars, i) \
  &((utf_t *) (chars)->objs)[i]

#define imp_new(toks, capa) \
  ary_new(toks, capa, sizeof(tok_t *))

#define imp_add(toks, tok) \
  ary_add(toks, tok, sizeof(tok_t *))

#define tok_new(toks) \
  ary_new(toks, 1, sizeof(tok_t))

#define tok_add(toks, tok) \
  ary_add(toks, tok, sizeof(tok_t))

#define cal_new(toks) \
  ary_new(toks, 1, sizeof(cal_t *))

#define cal_add(toks, tok) \
  ary_add(toks, tok, sizeof(cal_t *))

#define req_new(reqs) \
  ary_new(reqs, 2, sizeof(ary_t))

#define req_add(reqs, req) \
  ary_add(reqs, req, sizeof(ary_t))

#define src_new(srcs) \
  ary_new(srcs, 2, sizeof(src_t *))

#define src_add(srcs, src) \
  ary_add(srcs, src, sizeof(src_t *))

#define utf_new(chars) \
  ary_new(chars, 2, sizeof(utf_t))

#define utf_add(chars, c) \
  ary_add(chars, c, sizeof(utf_t))

utf_t *
tok_new_str(utf_t * str, size_t len) {
  utf_t * buf = malloc(len + 1);
  memcpy(buf, str, len);
  buf[len] = '\0';
  return buf;
}

utf_t *
tok_cat_str(utf_t * x, size_t xlen, utf_t * y, size_t ylen) {
  size_t len = xlen + ylen;
  utf_t * buf = malloc(len + 1);
  memcpy(buf, x, xlen);
  memcpy(buf + xlen, y, ylen);
  buf[len] = '\0';
  return buf;
}

void
tok_poffset(tok_t * tok, FILE * out, size_t offset) {
  size_t i = 0;
  while (i < tok->len) {
    utf_t * str = &tok->string[i];
    size_t len = utf8_len(str);
    if (offset > 0) {
      offset--;
    } else {
      utf_t buf[5] = {0};
      memcpy(buf, str, len);
      fprintf(out, "%s", buf);
    }
    i += len;
  }
}

void
tok_ptail(tok_t * tok, FILE * out) {
  tok_poffset(tok, out, 1);
}

void
tok_print(tok_t * tok, FILE * out) {
  tok_poffset(tok, out, 0);
}

#define cal_ptail(tok, out) \
  tok_ptail((tok_t *) (tok), out)

#define cal_print(tok, out) \
  tok_print((tok_t *) (tok), out)

int
tok_first_not_term(ary_t * toks) {
  size_t i = 0;
  for (; i < toks->len; i++) {
    tok_t * tok = tok_get(toks, i);
    if (tok->def != TERM) break;
  }
  return i;
}

void
toks_cprint(src_t * src, ary_t * toks, size_t i, FILE * fsrc) {
  for (; i < toks->len; i++) {
    utf_t * cname = src->cname;
    tok_t * tok = tok_get(toks, i);
    def_t def = tok->def;
    if (def == TSELF ||
        def == CTSELF) {
      fprintf(fsrc, "%s_t", cname);
    } else if (def == TCLASS ||
               def == CTCLASS) {
      fprintf(fsrc, "%s_class_t", cname);
    } else if (def == SELF ||
               def == CSELF) {
      fprintf(fsrc, "%s_t * ", cname);
      tok_print(tok, fsrc);
    } else {
      tok_print(tok, fsrc);
    }
  }
}

void
cparse_require(cclass_t * class, scan_t * scan, tok_t * tok) {
  parse_match(scan, CSPACE);
  parse_match(scan, CQUOTE);
  ary_t req = {0};
  utf_new(&req);
  * tok = parse_next(scan);
  while (!parse_test(tok, CQUOTE)) {
    utf_t * string = tok->string;
    size_t len = tok->len;
    if (parse_test(tok, CBQUOTE)) {
      string++, len--;
    }
    size_t i = 0;
    for (; i < len; i++) {
      utf_t * str = &string[i];
      utf_add(&req, str);
    }
    * tok = parse_next(scan);
  }
  * tok = parse_next(scan);
  req_add(&class->reqs, &req);
}

void
cparse_raw(cclass_t * class, scan_t * scan, tok_t * tok) {
  tok_t * first = 0;
  src_t * src = 0;
  while (!parse_test(tok, CCLASS) &&
         !scan->eof) {
    if (src == 0) {
      src = calloc(1, sizeof(ary_t) + sizeof(tok_t));
      tok_new(&src->toks);
      src_add(&class->srcs, &src);
    }
    if (parse_test(tok, CREQUIRE)) {
      cparse_require(class, scan, tok);
      first = tok;
      tok_add(&src->toks, tok);
    } else if (src->toks.len == 0) {
      first = tok_add(&src->toks, tok);
    } else {
      first->len += tok->len;
    }
    * tok = parse_next(scan);
  }
}

tok_t *
tok_cpy(tok_t * original) {
  tok_t * new = calloc(1, sizeof(tok_t));
  * new = * original;
  return new;
}

tok_t *
cal_add_cpy(src_t * src, tok_t * tok) {
  tok_t * new = tok_cpy(tok);
  cal_add(&src->toks, &new);
  return new;
}

size_t
cparse_terms(src_t * src, scan_t * scan, tok_t * tok) {
  * tok = parse_next(scan);
  size_t declend = src->toks.len;
  while (parse_test(tok, CTERM)) {
    cal_add_cpy(src, tok);
    declend = src->toks.len;
    * tok = parse_next(scan);
  }
  return declend;
}

#define STRLEN(str) lenof(str) - 1

static utf_t basename[] = "Object";
static tok_t baseclass = {ID, STRLEN(basename), basename};

size_t
cparse_def(cclass_t * class, src_t * src, scan_t * scan, tok_t * next) {
  scan->states = scan_states;
  parse_match(scan, TERM);
  src->class = parse_term(scan, ID);
  tok_t tok = parse_next(scan);
  if (parse_test(&tok, EXTENDS)) {
    parse_match(scan, TERM);
    src->super = parse_term(scan, ID);
    parse_term(scan, LBLOCK);
  } else {
    tok_t * cls = &src->class;
    if (cls->len != STRLEN(basename) ||
        memcmp(cls->string, basename, STRLEN(basename)) != 0) {
      src->super = baseclass;
    }
    parse_check(&tok, LBLOCK);
    parse_match(scan, TERM);
  }
  parse_term(scan, STRUCT);
  parse_match(scan, LBLOCK);
  size_t level = 1;
  scan->states = scan_cstates;
  tok = parse_next(scan);
  tok_new(&src->strukt);
  tok_add(&src->strukt, &tok);
  while (1) {
    if (parse_test(&tok, LBLOCK)) {
      level++;
    } else if (parse_test(&tok, RBLOCK)) {
      level--;
    }
    if (level == 0) break;
    tok_add(&src->strukt, &tok);
    tok = parse_next(scan);
  }
  scan->states = scan_states;
  parse_match(scan, TERM);
  tok = parse_next(scan);
  if (parse_test(&tok, CLASS)) {
    parse_match(scan, TERM);
    parse_match(scan, LBLOCK);
    scan->states = scan_cstates;
    meth_t meth = {0};
    meth_new(src, 4);
    while (1) {
      tok_t tok = parse_next(scan);
      if (parse_test(&tok, RBLOCK)) {
        break;
      } else if (parse_test(&tok, METHOD)) {
        meth.or.name = tok;
      } else if (parse_test(&tok, STAT)) {
        meth_add(src, &meth);
        meth = (meth_t) {0};
      } else {
        if (meth.nm.name.objs == NULL) {
          tok_new(&meth.nm.name);
          tok_add(&meth.nm.name, &tok);
        } else if (meth.or.name.string == NULL) {
          tok_add(&meth.or.ret, &tok);
        } else if (meth.or.arg.objs == NULL) {
          tok_new(&meth.or.arg);
          tok_add(&meth.or.arg, &tok);
        } else {
          tok_add(&meth.or.arg, &tok);
        }
      }
    }
    ary_free(&meth.nm.name);
    scan->states = scan_states;
    parse_match(scan, TERM);
    parse_match(scan, RBLOCK);
  } else {
    meth_new(src, 1);
    parse_check(&tok, RBLOCK);
  }
  scan->states = cscan_states;
  return cparse_terms(src, scan, next);
}

void
cal_add_cat(src_t * src, tok_t * prev, tok_t * next) {
  tok_t * new = tok_cpy(prev);
  new->len += next->len;
  cal_add(&src->toks, &new);
}

void
cal_add_two(src_t * src, tok_t * self, tok_t * name) {
  cal_t * tok = calloc(1, sizeof(cal_t));
  tok->self = * self;
  tok->name = * name;
  cal_add(&src->toks, &tok);
}

void
cparse_call(src_t * src, scan_t * scan, tok_t * self) {
  tok_t next = parse_next(scan);
  if (parse_test(&next, CCALL)) {
    self->def = CIDMCALL;
    cal_add_two(src, self, &next);
  } else if (parse_test(&next, CSTCALL)) {
    self->def = CSTMCALL;
    cal_add_two(src, self, &next);
  } else if (parse_test(&next, CSPACE)) {
    cal_add_cpy(src, self);
    cal_add_cpy(src, &next);
  } else if (parse_test(&next, CTERM)) {
    cal_add_cpy(src, self);
    cal_add_cpy(src, &next);
  } else {
    cal_add_cat(src, self, &next);
  }
}

void
cparse_scall(src_t * src, scan_t * scan, tok_t * self, tok_t * meth) {
  tok_t next = parse_next(scan);
  if (parse_test(&next, CCALL)) {
    if (meth->def == CCMETHOD) {
      self->def = CSUCMCALL;
    } else {
      self->def = CSUMCALL;
    }
    cal_add_two(src, self, &next);
  } else if (parse_test(&next, CLPARE)) {
    * self = * meth;
    if (meth->def == CCMETHOD) {
      self->def = CSUCCALL;
    } else {
      self->def = CSUCALL;
    }
    cal_add_cpy(src, self);
    cal_add_cpy(src, &next);
  } else {
    cal_add_cat(src, self, &next);
  }
}

def_t
cparse_cmeth(src_t * src, scan_t * scan, tok_t * tok, size_t declend) {
  def_t def = CMETHOD;
  tok_t * new = cal_add_cpy(src, tok);
  imp_add(&src->imps, &new);
  size_t paras = 0;
  * tok = parse_next(scan);
  if (parse_test(tok, CLPARE)) {
    meth_t meth = {0};
    tok_new(&meth.nm.name);
    size_t len = src->toks.len;
    size_t i = declend;
    tok_t * arg = (tok_t *) cal_get(&src->toks, i);
    if (parse_test(arg, CSTATIC)) {
      i++;
      arg = (tok_t *) cal_get(&src->toks, i);
      while (parse_test(arg, CSPACE)) {
        i++;
        arg = (tok_t *) cal_get(&src->toks, i);
      }
    }
    for (; i < len - 1; i++) {
      tok_t * ret = (tok_t *) cal_get(&src->toks, i);
      if (!parse_test(ret, CTERM)) {
        tok_add(&meth.or.ret, ret);
      }
    }
    cal_add_cpy(src, tok);
    tok_new(&meth.or.arg);
    tok_add(&meth.or.arg, tok);
    paras++;
    meth.or.name = * new;
    meth.or.name.def = CDMETHOD;
    * tok = parse_next(scan);
    if (tok->def != CSELF) {
      def = CCMETHOD;
    }
    cal_add_cpy(src, tok);
    if (!parse_test(tok, CTERM)) {
      tok_add(&meth.or.arg, tok);
    }
    while (1) {
      * tok = parse_next(scan);
      cal_add_cpy(src, tok);
      if (parse_test(tok, CRPARE)) {
        paras--;
        if (paras == 0) {
          tok_add(&meth.or.arg, tok);
          meth_add(src, &meth);
          break;
        }
      } else if (parse_test(tok, CLPARE)) {
        paras++;
      }
      if (!parse_test(tok, CTERM)) {
        tok_add(&meth.or.arg, tok);
      }
    }
  } else {
    cal_add_cpy(src, tok);
  }
  return def;
}

size_t
cparse_com(src_t * src, scan_t * scan, tok_t * tok) {
  cal_add_cpy(src, tok);
  * tok = parse_next(scan);
  while (!parse_test(tok, CTERM)) {
    cal_add_cpy(src, tok);
    * tok = parse_next(scan);
  }
  cal_add_cpy(src, tok);
  return cparse_terms(src, scan, tok);
}

size_t
cparse_coms(src_t * src, scan_t * scan, tok_t * tok) {
  cal_add_cpy(src, tok);
  * tok = parse_next(scan);
  while (!parse_test(tok, CCOMS_END)) {
    cal_add_cpy(src, tok);
    * tok = parse_next(scan);
  }
  cal_add_cpy(src, tok);
  return cparse_terms(src, scan, tok);
}

void
cparse_typedef(src_t * src, scan_t * scan, tok_t * tok) {
  tok_t first = * tok;
  * tok = parse_next(scan);
  while (!parse_test(tok, CDECLEND)) {
    first.len += tok->len;
    * tok = parse_next(scan);
  }
  first.len += tok->len;
  ary_t * typs = &src->typs;
  tok_add(typs, &first);
  * tok = parse_next(scan);
  while (parse_test(tok, CTERM)) {
    * tok = parse_next(scan);
  }
}

void
cparse_src(cclass_t * class, scan_t * scan, tok_t * tok) {
  if (!parse_test(tok, CCLASS)) return;
  src_t * src = calloc(1, sizeof(src_t));
  src_add(&class->srcs, &src);
  cal_new(&src->toks);
  tok_new(&src->typs);
  size_t declend = cparse_def(class, src, scan, tok);
  imp_new(&src->imps, src->meths.len);
  tok_t meth = {0};
  while (!parse_test(tok, CCLASS) &&
         !scan->eof) {
    if (parse_test(tok, CEND)) {
      * tok = parse_next(scan);
      break;
    } else if (parse_test(tok, CTCLASS)) {
      cal_add_cpy(src, tok);
    } else if (parse_test(tok, CTSELF)) {
      cal_add_cpy(src, tok);
    } else if (parse_test(tok, CTYPEDEF)) {
      cparse_typedef(src, scan, tok);
      continue;
    } else if (parse_test(tok, CMETHOD)) {
      meth = * tok;
      meth.def = cparse_cmeth(src, scan, tok, declend);
    } else if (parse_test(tok, CSELF)) {
      tok->def = CID;
      cal_add_cpy(src, tok);
    } else if (parse_test(tok, CSUPER)) {
      cparse_scall(src, scan, tok, &meth);
    } else if (parse_test(tok, CID)) {
      cparse_call(src, scan, tok);
    } else if (parse_test(tok, CCALL)) {
      tok->def = CSEMCALL;
      cal_add_cpy(src, tok);
    } else if (parse_test(tok, CINSTANCE)) {
      cal_add_cpy(src, tok);
    } else if (parse_test(tok, CLPARE)) {
      cal_add_cpy(src, tok);
    } else if (parse_test(tok, CNSIGN)) {
      declend = cparse_com(src, scan, tok);
      continue;
    } else if (parse_test(tok, CCOM)) {
      declend = cparse_com(src, scan, tok);
      continue;
    } else if (parse_test(tok, CCOMS_BEG)) {
      declend = cparse_coms(src, scan, tok);
      continue;
    } else if (parse_test(tok, CDECLEND)) {
      cal_add_cpy(src, tok);
      declend = cparse_terms(src, scan, tok);
      continue;
    } else if (parse_test(tok, CRBRACE)) {
      cal_add_cpy(src, tok);
      declend = cparse_terms(src, scan, tok);
      continue;
    } else {
      cal_add_cpy(src, tok);
    }
    * tok = parse_next(scan);
  }
}

cclass_t *
cparse_header(utf_t * string, size_t size) {
  cclass_t * class = calloc(1, sizeof(cclass_t));
  req_new(&class->reqs);
  src_new(&class->srcs);
  scan_t scan = cscan_new(string, size);
  tok_t tok = parse_next(&scan);
  while (!scan.eof) {
    cparse_raw(class, &scan, &tok);
    cparse_src(class, &scan, &tok);
  }
  return class;
}

int
str_is_upcase(utf_t c) {
  return c >= 'A' && c <= 'Z';
}

int
str_is_dwcase(utf_t c) {
  return c >= 'a' && c <= 'z';
}

size_t
tok_word(utf_t * string, size_t len) {
  size_t upwords = 0;
  size_t i = 0;
  size_t prev = i;
  while (i < len) {
    utf_t * str = &string[i];
    size_t len = utf8_len(str);
    if (!(len == 1 &&
          str_is_upcase(* str))) {
      break;
    }
    prev = i;
    i += len;
    upwords++;
  }
  if (upwords <= 1) {
    while (i < len) {
      utf_t * str = &string[i];
      size_t len = utf8_len(str);
      if (len == 1 &&
          str_is_upcase(* str)) {
        break;
      }
      i += len;
    }
  } else {
    i = prev;
  }
  return i;
}

size_t
tok_words(tok_t * tok) {
  size_t words = 0;
  size_t i = 0;
  while (i < tok->len) {
    utf_t * str = &tok->string[i];
    size_t len = utf8_len(str);
    size_t wlen = tok_word(str, tok->len - i);
    if (wlen) {
      words++;
      i += wlen;
    } else {
      i += len;
    }
  }
  if (words == 0) words = 1;
  return words;
}

typedef int str_is_case_t(utf_t c);
typedef utf_t str_case_t(utf_t c);

utf_t
str_upcase(utf_t c) {
  return c - 0x20;
}

utf_t
str_dwcase(utf_t c) {
  return c + 0x20;
}

void
tok_case(utf_t * dest, utf_t * src, size_t len,
         str_is_case_t * cmp, str_case_t * yield) {
  size_t i = 0;
  while (i < len) {
    utf_t * str = &src[i];
    size_t len = utf8_len(str);
    memcpy(&dest[i], str, len);
    if (len == 1 &&
        cmp(* str)) {
      dest[i] = yield(* str);
    }
    i += len;
  }
}

void
tok_upcase(utf_t * dest, utf_t * src, size_t len) {
  tok_case(dest, src, len, str_is_dwcase, str_upcase);
}

void
tok_dwcase(utf_t * dest, utf_t * src, size_t len) {
  tok_case(dest, src, len, str_is_upcase, str_dwcase);
}

typedef void tok_case_t(utf_t * dest, utf_t * src, size_t len);

void
tok_inflect(utf_t * dest, tok_t * src, tok_case_t * yield) {
  size_t i = 0;
  while (i < src->len) {
    utf_t * str = &src->string[i];
    size_t len = utf8_len(str);
    size_t wlen = tok_word(str, src->len - i);
    if (wlen) {
      yield(dest, str, wlen);
      i += wlen;
      dest += wlen;
      if (i < src->len) {
        * dest++ = '_';
      }
    } else {
      memcpy(dest, str, len);
      i += len;
      dest += len;
    }
  }
}

// FooBar => FOO_BAR
void
tok_constantize(utf_t * dest, tok_t * src) {
  tok_inflect(dest, src, tok_upcase);
}

// FooBar => foo_bar
void
tok_underscore(utf_t * dest, tok_t * src) {
  tok_inflect(dest, src, tok_dwcase);
}

typedef void tok_inflect_t(utf_t * dest, tok_t * src);

utf_t *
class_inflect(tok_t * src, tok_inflect_t * yield) {
  utf_t * dest = tok_new_str(src->string,
                             src->len + tok_words(src) - 1);
  yield(dest, src);
  return dest;
}

h_table *
class_classes(cclass_t * class) {
  ary_t * srcs = &class->srcs;
  h_table * classes = h_init();
  size_t i = 0;
  for (; i < srcs->len; i++) {
    src_t * src = src_get(srcs, i);
    if (src->class.string != NULL) {
      tok_t * tok = &src->class;
      h_insert(classes, tok->string, (h_size_t) tok->len, (h_data_t) src);
    }
  }
  return classes;
}

void *
class_source(utf_t * fname, utf_t * string, size_t size) {
  cclass_t * class = cparse_header(string, size);
  class->string = string;
  h_table * classes = class_classes(class);
  h_entry * entry = classes->head;
  while (entry) {
    src_t * src = (src_t *) entry->val;
    tok_t * klass = &src->class;
    tok_t * super = &src->super;
    src->cname = class_inflect(klass, tok_underscore);
    src->sname = class_inflect(super, tok_underscore);
    entry = entry->back;
  }
  class->classes = classes;
  return class;
}

// C reverse methods
void
class_crmeths(cclass_t * class, src_t * src, h_table * meths) {
  if (!src) return;
  tok_t * super = &src->super;
  src_t * superclass = 0;
  int get = h_get(class->classes, super->string, super->len,
                  (h_data_t *) &superclass);
  if (!get && super->string != basename) {
    printf("Please require ");
    tok_print(super, stdout);
    printf(".\n");
    exit(0);
  }
  class_crmeths(class, superclass, meths);
  size_t len = src->meths.len;
  size_t mi = 0;
  for (; mi < len; mi++) {
    meth_t * meth = meth_get(src, mi);
    tok_t * name = &meth->or.name;
    utf_t * str = name->string + 1;
    size_t len = (h_size_t) (name->len - 1);
    h_insert(meths, str, len, (h_data_t) meth);
  }
}

h_table *
class_cmeths(cclass_t * class, src_t * src) {
  h_table * meths = h_init();
  class_crmeths(class, src, meths);
  return meths;
}

void
class_praw(src_t * src, FILE * fsrc) {
  ary_t * toks = &src->toks;
  size_t i = 0;
  for (; i < toks->len; i++) {
    tok_t * tok = tok_get(toks, i);
    tok_print(tok, fsrc);
  }
}

void
class_parg(cal_t * tok, cal_t * next, size_t * i, FILE * fsrc) {
  if (tok->self.def == CLPARE) {
    * i += 1;
    if (next->self.def != CRPARE) {
      fprintf(fsrc, ", ");
    }
  } else {
    fprintf(fsrc, ")");
  }
}

// print class method arguments (without first 'self' argument)
void
class_pcarg(cal_t * tok, size_t * i, FILE * fsrc) {
  if (tok->self.def == CLPARE) {
    * i += 1;
  } else {
    fprintf(fsrc, ")");
  }
}

void
class_ptyps(src_t * src, FILE * fsrc) {
  ary_t * typs = &src->typs;
  size_t i = 0;
  for (; i < typs->len; i++) {
    tok_t * tok = tok_get(typs, i);
    tok_ptail(tok, fsrc);
    fprintf(fsrc, "\n");
  }
}

// print first variable of struct
void
class_pshead(utf_t * cname, FILE * fsrc) {
  fprintf(fsrc,
          "  struct %s {\n"
          "    union {\n"
          "      %s_class_t * class;\n"
          "      %s_class_t * _;\n"
          "    };", cname, cname, cname);
}

// print 2th ... last variables of struct
void
class_pstail(src_t * src, src_t * base, h_table * classes, FILE * fsrc) {
  tok_t * super = &base->super;
  if (super->string != basename) {
    src_t * superclass = 0;
    h_get(classes, super->string, super->len, (h_data_t *) &superclass);
    class_pstail(src, superclass, classes, fsrc);
  }
  toks_cprint(src, &base->strukt, 1, fsrc);
}

void
class_pend(FILE * fsrc) {
  fprintf(fsrc, "};\n\n");
}

void
class_pstruct(cclass_t * class, src_t * src, h_table * classes, FILE * fsrc) {
  class_pshead(src->cname, fsrc);
  class_pstail(src, src, class->classes, fsrc);
  class_pend(fsrc);
}

void
class_pmhead(utf_t * cname, utf_t * sname, FILE * fsrc) {
  fprintf(fsrc,
          "struct %s_class {\n"
          "  char * name;\n"
          "  %s_class_t * (* super)(%s_t *);\n", cname, sname, cname);
}

void
class_pmtail(cclass_t * class, src_t * src, h_table * meths, FILE * fsrc) {
  h_entry * entry = meths->head;
  for (; entry; entry = entry->back) {
    meth_t * meth = (meth_t *) entry->val;
    tok_t * name = &meth->or.name;
    if (name->string != NULL) {
      fprintf(fsrc, "  ");
      size_t i = tok_first_not_term(&meth->or.ret);
      toks_cprint(src, &meth->or.ret, i, fsrc);
      if (name->def == CDMETHOD) {
        fprintf(fsrc, " (* ");
        tok_ptail(name, fsrc);
        fprintf(fsrc, ")");
      } else {
        tok_ptail(name, fsrc);
      }
      toks_cprint(src, &meth->or.arg, 0, fsrc);
      fprintf(fsrc, ";\n");
    }
  }
}

void
class_pmstruct(cclass_t * class, src_t * src, h_table * meths, FILE * fsrc) {
  class_pmhead(src->cname, src->sname, fsrc);
  class_pmtail(class, src, meths, fsrc);
  class_pend(fsrc);
}

// print struct type
void
class_pctyp(utf_t * cname, FILE * fsrc) {
  fprintf(fsrc,
          "typedef struct %s_class %s_class_t;\n"
          "typedef struct %s %s_t;\n\n", cname, cname, cname, cname);
}

void
class_pmdecl(src_t * src, h_table * meths, FILE * fsrc) {
  h_entry * entry = meths->head;
  for (; entry; entry = entry->back) {
    meth_t * meth = (meth_t *) entry->val;
    tok_t * name = &meth->or.name;
    if (name->string != NULL) {
      size_t i = tok_first_not_term(&meth->or.ret);
      toks_cprint(src, &meth->or.ret, i, fsrc);
      fprintf(fsrc, " %s_method_", src->cname);
      tok_ptail(name, fsrc);
      toks_cprint(src, &meth->or.arg, 0, fsrc);
      fprintf(fsrc, ";\n");
    }
  }
}

void
class_pextn(src_t * src, FILE * fsrc) {
  utf_t * cname = src->cname;
  fprintf(fsrc, "extern %s_class_t ", cname);
  tok_print(&src->class, fsrc);
  fprintf(fsrc, ";\n");
}

void
class_pbases(cclass_t * class, FILE * fsrc) {
  utf_t object[] = "object";
  class_pctyp(object, fsrc);
  class_pmhead(object, object, fsrc);
  class_pend(fsrc);
  class_pshead(object, fsrc);
  class_pend(fsrc);
  h_table * rclasses = class->rclasses;
  h_entry * entry = rclasses->head;
  for (; entry; entry = entry->back) {
    src_t * src = (src_t *) entry->val;
    class_pctyp(src->cname, fsrc);
  }
  entry = rclasses->head;
  for (; entry; entry = entry->back) {
    src_t * src = (src_t *) entry->val;
    class_ptyps(src, fsrc);
    h_table * meths = class_cmeths(class, src);
    class_pmstruct(class, src, meths, fsrc);
    class_pstruct(class, src, class->classes, fsrc);
    class_pextn(src, fsrc);
    class_pmdecl(src, meths, fsrc);
    h_free(meths);
  }
}

void
class_pmsuper(src_t * src, FILE * fsrc) {
  tok_t * super = &src->super;
  utf_t * cname = src->cname;
  utf_t * sname = src->sname;
  fprintf(fsrc,
          "\n%s_class_t *\n"
          "%s_method_super(%s_t * self) {\n", sname, cname, cname);
  if (super->string == basename) {
    fprintf(fsrc, "  return 0;\n}\n\n");
  } else {
    fprintf(fsrc, "  return &");
    tok_print(super, fsrc);
    fprintf(fsrc, ";\n}\n\n");
  }
}

void
class_pcmeth(cclass_t * class, src_t * src, h_size_t meths_len, FILE * fsrc) {
  src_t * klass = src;
  h_table * meths = h_init();
  size_t mi = 0;
  while (1) {
    tok_t * super = &klass->super;
    utf_t * cname = klass->cname;
    ary_t * imps = &klass->imps;
    size_t i = 0;
    for (; i < imps->len; i++) {
      tok_t * tok = imp_get(imps, i);
      if (h_contains(meths, tok->string, tok->len)) continue;
      h_insert(meths, tok->string, tok->len, 0);
      fprintf(fsrc, "  .");
      tok_ptail(tok, fsrc);
      if (klass == src) {
        fprintf(fsrc, " = &%s_method_", cname);
        tok_ptail(tok, fsrc);
      } else {
        fprintf(fsrc, " = (void *) &%s_method_", cname);
        tok_ptail(tok, fsrc);
      }
      if (mi != meths_len - 1) {
        fprintf(fsrc, ",");
      }
      fprintf(fsrc, "\n");
      mi++;
    }
    h_table * classes = class->classes;
    int get = h_get(classes, super->string, super->len, (h_data_t *) &klass);
    if (!get) break;
  }
  h_free(meths);
}

void
class_pclass(cclass_t * class, src_t * src, h_table * meths, FILE * fsrc) {
  utf_t * cname = src->cname;
  fprintf(fsrc, "%s_class_t ", cname);
  tok_print(&src->class, fsrc);
  fprintf(fsrc, " = {\n  .name = \"");
  tok_print(&src->class, fsrc);
  fprintf(fsrc, "\",\n  .super = &%s_method_super,\n", cname);
  class_pcmeth(class, src, meths->len, fsrc);
  fprintf(fsrc, "};\n\n");
}

void
class_pstructs(cclass_t * class, src_t * src, FILE * fsrc) {
  utf_t * cname = src->cname;
  class_pctyp(cname, fsrc);
  class_ptyps(src, fsrc);
  h_table * meths = class_cmeths(class, src);
  class_pmstruct(class, src, meths, fsrc);
  class_pstruct(class, src, class->classes, fsrc);
  class_pmdecl(src, meths, fsrc);
  class_pmsuper(src, fsrc);
  class_pclass(class, src, meths, fsrc);
  h_free(meths);
}

void
class_freqs(cclass_t * class) {
  ary_t * reqs = &class->reqs;
  size_t i = 0;
  for (; i < reqs->len; i++) {
    ary_t * req = req_get(reqs, i);
    ary_free(req);
  }
  ary_free(reqs);
}

void
class_fsrc(src_t * src) {
  if (!src->class.string) {
    ary_free(&src->toks);
    free(src);
  }
}

void
class_fsrcs(cclass_t * class) {
  ary_t * srcs = &class->srcs;
  size_t i = 0;
  for (; i < srcs->len; i++) {
    src_t * src = src_get(srcs, i);
    class_fsrc(src);
  }
  ary_free(srcs);
}

void
class_free(cclass_t * class) {
  class_freqs(class);
  class_fsrcs(class);
}

void
class_fstruct(src_t * src) {
  ary_free(&src->strukt);
}

void
class_fmeths(src_t * class) {
  size_t len = class->meths.len;
  size_t i = 0;
  for (; i < len; i++) {
    meth_t * meth = meth_get(class, i);
    if (meth->or.name.string == NULL) {
      ary_free(&meth->nm.name);
    } else {
      ary_free(&meth->or.ret);
      ary_free(&meth->or.arg);
    }
  }
  ary_free(&class->meths);
}

void
class_ftoks(src_t * src) {
  ary_t * toks = &src->toks;
  if (src->class.string) {
    size_t i = 0;
    for (; i < toks->len; i++) {
      cal_t * tok = cal_get(toks, i);
      free(tok);
    }
  }
  ary_free(toks);
}

void
class_fimps(src_t * src) {
  ary_free(&src->imps);
}

void
class_ftyps(src_t * src) {
  ary_free(&src->typs);
}

void
class_fclasses(cclass_t * class, h_table * fnames, utf_t * fname) {
  h_table * classes = class->classes;
  h_entry * entry = classes->head;
  while (entry) {
    src_t * src = (src_t *) entry->val;
    class_ftoks(src);
    class_fstruct(src);
    class_fmeths(src);
    class_fimps(src);
    class_ftyps(src);
    free(src->cname);
    free(src->sname);
    free(src);
    entry = entry->back;
  }
  h_free(classes);
  entry = fnames->head;
  while (entry) {
    utf_t * name = entry->key;
    cclass_t * klass = (cclass_t *) entry->val;
    if (name != fname) free(name);
    h_free(klass->rclasses);
    free(klass->string);
    free(klass);
    entry = entry->back;
  }
  h_free(fnames);
}

fread_t build_source;

void
class_require(cclass_t * class, utf_t * fname, h_table * fnames) {
  class->rclasses = h_init();
  h_table * rclasses = class->rclasses;
  h_table * classes = class->classes;
  ary_t * reqs = &class->reqs;
  size_t i = 0;
  for (; i < reqs->len; i++) {
    ary_t * req = req_get(reqs, i);
    utf_t * str = utf_get(req, 0);
    size_t len = req->len;
    utf_t * fname = tok_new_str(str, len);
    int get = h_get(fnames, fname, len, (h_data_t *) &class);
    if (!get) {
      class = file_read(1, fname, build_source, fnames);
    }
    h_table * cclasses = class->classes;
    h_merge(rclasses, cclasses);
    h_free(cclasses);
  }
  h_merge(classes, rclasses);
}

void
class_psrc(src_t * src, FILE * fsrc) {
  ary_t * toks = &src->toks;
  size_t i = 0;
  for (; i < toks->len; i++) {
    cal_t * tok = cal_get(toks, i);
    def_t def = tok->self.def;
    if (def != CTERM) break;
  }
  tok_t * class = &src->class;
  utf_t * cname = src->cname;
  for (; i < toks->len; i++) {
    cal_t * tok = cal_get(toks, i);
    cal_t * next = cal_get(toks, i + 1);
    cal_t * nnxt = cal_get(toks, i + 2);
    tok_t * name = &tok->name;
    def_t def = tok->self.def;
    if (def == CTSELF) {
      fprintf(fsrc, "%s_t", cname);
    } else if (def == CTCLASS) {
      fprintf(fsrc, "%s_class_t", cname);
    } else if (def == CMETHOD) {
      fprintf(fsrc, "%s_method_", cname);
      cal_ptail(tok, fsrc);
    } else if (def == CSELF) {
      fprintf(fsrc, "%s_t * ", cname);
      cal_print(tok, fsrc);
    } else if (def == CINSTANCE) {
      fprintf(fsrc, "self->");
      cal_ptail(tok, fsrc);
    } else if (def == CSUCALL) {
      fprintf(fsrc, "self->_.super()->");
      cal_ptail(tok, fsrc);
      fprintf(fsrc, "(self");
      class_parg(next, nnxt, &i, fsrc);
    } else if (def == CSUCCALL) {
      tok_print(class, fsrc);
      fprintf(fsrc, ".super(0)->");
      cal_ptail(tok, fsrc);
      fprintf(fsrc, "(");
      class_pcarg(next, &i, fsrc);
    } else if (def == CSUMCALL) {
      fprintf(fsrc, "self->_.super()->");
      tok_ptail(name, fsrc);
      fprintf(fsrc, "(self");
      class_parg(next, nnxt, &i, fsrc);
    } else if (def == CSUCMCALL) {
      tok_print(class, fsrc);
      fprintf(fsrc, ".super(0)->");
      tok_ptail(name, fsrc);
      fprintf(fsrc, "(");
      class_pcarg(next, &i, fsrc);
    } else if (def == CSEMCALL) {
      fprintf(fsrc, "self->_->");
      cal_ptail(tok, fsrc);
      fprintf(fsrc, "(self");
      class_parg(next, nnxt, &i, fsrc);
    } else if (def == CIDMCALL) {
      cal_print(tok, fsrc);
      fprintf(fsrc, "->_->");
      tok_ptail(name, fsrc);
      fprintf(fsrc, "(");
      cal_print(tok, fsrc);
      class_parg(next, nnxt, &i, fsrc);
    } else if (def == CSTMCALL) {
      cal_print(tok, fsrc);
      fprintf(fsrc, "._->");
      tok_ptail(name, fsrc);
      fprintf(fsrc, "(&");
      cal_print(tok, fsrc);
      class_parg(next, nnxt, &i, fsrc);
    } else {
      cal_print(tok, fsrc);
    }
  }
}

void
class_gen(cclass_t * class, FILE * fsrc) {
  class_pbases(class, fsrc);
  ary_t * srcs = &class->srcs;
  size_t i = 0;
  for (; i < srcs->len; i++) {
    src_t * src = src_get(srcs, i);
    if (src->class.string == NULL) {
      class_praw(src, fsrc);
    } else {
      class_pstructs(class, src, fsrc);
      class_psrc(src, fsrc);
    }
  }
}

void *
build_source(utf_t * fname, utf_t * string, size_t size, void * fnames) {
  cclass_t * class = class_source(fname, string, size);
  h_insert(fnames, fname, strlen(fname), (h_data_t) class);
  class_require(class, fname, fnames);
  // file write name
  utf_t ext[] = ".c";
  utf_t * fwname = tok_cat_str(fname, strlen(fname),
                               ext,   strlen(ext));
  printf("Generating %s ... ", fwname);
  FILE * fsrc = fopen(fwname, "w");
  class_gen(class, fsrc);
  fclose(fsrc);
  printf("OK\n");
  free(fwname);
  class_free(class);
  return class;
}

void *
build_source_start(utf_t * fname, utf_t * string, size_t size, void * unused) {
  h_table * fnames = h_init();
  cclass_t * class = build_source(fname, string, size, fnames);
  class_fclasses(class, fnames, fname);
  return class;
}

typedef enum {
  SOURCE,
  HEADER,
  NOP
} action;

action
scan_args(int argc, utf_t ** argv) {
  if (argc <= 1) {
    puts("no input file");
    exit(0);
  }
  if (argc == 2) {
    return SOURCE;
  }
  if (argc == 3 &&
      strcmp(argv[1], "-h") == 0) {
    return HEADER;
  }
  return NOP;
}

int
main(int argc, utf_t ** argv) {
  action act = scan_args(argc, argv);
  if (act == SOURCE) {
    file_read(argc - 1, argv[1], build_source_start, 0);
  }
  if (act == HEADER) {
    //file_read(argc - 2, argv[2], build_header, 0);
  }
  return 0;
}
