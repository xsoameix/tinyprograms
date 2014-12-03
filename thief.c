#include <stdio.h>

typedef enum {
  ITOR_BEFORE,
  ITOR
} ret_t;

typedef long long num_t;
typedef struct {
  num_t arg_begin;
  num_t arg_sum;
  num_t loc_i;
  ret_t ret;
} stack_t;

#define LEN 310

num_t total, len;
num_t items[LEN];
num_t stack_len;
stack_t stacks[LEN];

void
scan_items(void) {
  num_t i = 0;
  for (; i < len; i++) {
    scanf("%lld", &items[i]);
  }
}

void
knapsack(void) {
  stack_len = 0;
  stacks[stack_len++] = (stack_t) {
    .arg_begin = 0,
    .arg_sum = 0,
    .loc_i = 0,
    .ret = ITOR_BEFORE
  };
  while (stack_len) {
    stack_t * _ = &stacks[stack_len - 1];
    if (_->ret == ITOR_BEFORE) {
      if (_->arg_sum > total) {
        stack_len--;
      } else if (_->arg_sum == total) {
        num_t i = 0;
        for (; i < stack_len - 1; i++) {
          printf("%lld ", items[stacks[i].loc_i - 1]);
        }
        puts("");
        return;
      } else {
        _->ret = ITOR;
      }
    } else if (_->ret == ITOR) {
      if (_->loc_i >= len) {
        stack_len--;
      } else {
        stacks[stack_len++] = (stack_t) {
          .arg_begin = _->arg_begin + 1,
              .arg_sum = _->arg_sum + items[_->loc_i],
              .loc_i = _->loc_i + 1,
              .ret = ITOR_BEFORE
        };
        _->loc_i++;
        _->ret = ITOR;
      }
    }
  }
  printf("It is impossible.\n");
}

int
main(void) {
  while (scanf("%lld%lld", &total, &len) == 2) {
    scan_items();
    knapsack();
  }
  return 0;
}
