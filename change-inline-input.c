#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int indent = 0;

int
change(int price, int * currencies, int currencies_len) {
  static int min_change[50100];
  min_change[0] = 0;
  int i = 1;
  for (; i <= price; i++) {
    int min = INT_MAX;
    int currency_i = 0;
    for (; currency_i < currencies_len; currency_i++) {
      int remain = i - currencies[currency_i];
      if (remain < 0) continue;
      int the_change = min_change[remain] + 1;
      min = the_change < min ? the_change : min;
    }
    if (min == INT_MAX) {
      min_change[i] = 0;
    } else {
      min_change[i] = min;
    }
    //printf("%d ", min_change[i]);
  }
  //puts("");
  return min_change[price];
}

int *
create_currencies(int len) {
  static int currencies[110];
  memset(currencies, 0, sizeof(currencies));
  return currencies;
  //return calloc(len, sizeof(int));
}

int
main(void) {
  int currencies_len, price;
  while (1) {
    scanf("%d", &currencies_len);
    if (currencies_len == 0) break;
    int * currencies = create_currencies(currencies_len);;
    int i = 0;
    for (; i < currencies_len; i++) {
      scanf("%d", &currencies[i]);
    }
    scanf("%d", &price);
    printf("%d\n", change(price, currencies, currencies_len));
    //free(currencies);
  }
  return 0;
}
