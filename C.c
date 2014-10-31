#include <stdio.h>
#include <stdlib.h>

typedef long long bnum_t;

typedef struct {
  int len;
  int start;
  bnum_t * numbers;
} fact_t;

fact_t *
create_fact(int n) {
  int fact_size = sizeof(fact_t);
  int num_size = n * sizeof(bnum_t);
  fact_t * fact = calloc(1, fact_size + num_size);
  fact->numbers = (void *) fact + fact_size;
  int i = 0;
  for (; i < n; i++) {
    fact->numbers[i] = i + 1;
  }
  fact->len = n;
  fact->start = 0;
  return fact;
}

bnum_t
gcd(bnum_t x, bnum_t y) {
  bnum_t z = x;
  for (; !(x % z == 0 && y % z == 0); z--);
  return z;
}

void
fact_div(fact_t * x, fact_t * y) {
  int y_i = y->start;
  for (; y_i < y->len; y_i++) {
    int x_i = x->start;
    //printf("/ %lld\n", y->numbers[y_i]);
    for (; x_i < x->len; x_i++) {
      bnum_t gcd_num = gcd(x->numbers[x_i], y->numbers[y_i]);
      x->numbers[x_i] /= gcd_num;
      y->numbers[y_i] /= gcd_num;
      //printf("%lld / %lld\n", x->numbers[x_i], gcd_num);
      if (y->numbers[y_i] == 1) {
        break;
      }
    }
  }
}

bnum_t
fact_num(fact_t * n) {
  bnum_t num = 1;
  int i = n->start;
  for (; i < n->len; i++) {
    //printf("%lld * %lld\n", num, n->numbers[i]);
    num *= n->numbers[i];
  }
  return num;
}

void
print_fact(fact_t * n) {
  int i = n->start;
  for (; i < n->len; i++) {
    printf("%lld ", n->numbers[i]);
  }
  puts("");
}

bnum_t
combination(int n, int m) {
  fact_t * fact_n = create_fact(n);
  m = m > (n-m) ? m : n-m;
  fact_n->start = m;
  fact_t * fact_n_m = create_fact(n-m);
  fact_div(fact_n, fact_n_m);
  //print_fact(fact_n);
  bnum_t num = fact_num(fact_n);
  free(fact_n);
  free(fact_n_m);
  return num;
}

int
main(void) {
  int n, m;
  while (1) {
    scanf("%d%d", &n, &m);
    if (n == 0 &&
        m == 0) break;
    printf("%lld\n", combination(n, m));
  }
  return 0;
}
