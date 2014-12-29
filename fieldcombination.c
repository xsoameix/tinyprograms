#include <stdio.h>
#include <stdlib.h>

typedef long long num_t;

#define LEN 26

num_t n; // field number
num_t m; // member number
num_t ret;

typedef struct {
  num_t act;
  num_t rej;
} mem_t;

mem_t mem[LEN];

#define SET_BIT(x, n) x |= (1 << (n))

void
print_ret(num_t the_ret) {
  num_t i = 0;
  num_t get = 1;
  for (; i < n; i++) {
    if (get & the_ret) {
      printf("%c", (char) i + 'A');
    }
    get <<= 1;
  }
  puts("");
  fflush(stdout);
}

void
scan_mem(void) {
  num_t i = 0;
  for (; i < m; i++) {
    mem[i] = (mem_t) {0, 0};
    while (1) {
      char c, f;
      scanf("%c", &c);
      if (c == ';') {
        scanf("\n");
        break;
      }
      scanf("%c", &f);
      num_t num = f - 'A';
      if (c == '+') {
        SET_BIT(mem[i].act, num);
      } else {
        SET_BIT(mem[i].rej, num);
      }
    }
  }
  ret = 0;
}

void
produce(void) {
  num_t i = 0;
  num_t len = 1 << n;
  for (; i < len; i++) {
    num_t mi = 0;
    num_t ok = 1;
    for (; mi < m && ok; mi++) {
      printf("%llX", i);
      printf(" %llX", mem[mi].act);
      printf(" %llX,", mem[mi].rej);
      printf(" %s", (mem[mi].act & i) != 0 ? "t" : "f");
      printf(" %s\n", (mem[mi].rej & i) == 0 ? "t" : "f");
      fflush(stdout);
      if ((mem[mi].act & i) != 0 || (mem[mi].rej != 0 && (mem[mi].rej & i) == 0)) {
        // it's ok
      } else {
        ok = 0;
      }
    }
    if (ok) {
      print_ret(i);
      return;
    } else {
      //print_ret(i);
    }
  }
  printf("NO\n");
}

int
main(void) {
  while (1) {
    scanf("%lld", &n);
    scanf("%lld\n", &m);
    if (!n && !m) break;
    scan_mem();
    produce();
  }
  return 0;
}
