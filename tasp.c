#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int create_time;
  int solve_time;
} question_t;

int
cmp_question(const void * a, const void * b) {
  const question_t * q_a = a;
  const question_t * q_b = b;
  int q_a_priority = q_a->solve_time - q_a->create_time;
  int q_b_priority = q_b->solve_time - q_b->create_time;
  if (q_a_priority >= 0 && q_b_priority < 0) {
    return -1;
  }
  if (q_a_priority < 0 && q_b_priority >= 0) {
    return 1;
  }
  if (q_a_priority >= 0 && q_b_priority >= 0) {
    return q_a->create_time - q_b->create_time;
  } else {
    return q_b->solve_time - q_a->solve_time;
  }
}

void
sort_questions(question_t * qs, int len) {
  qsort(qs, len, sizeof(question_t), cmp_question);
}

int
min_questions_solve_time(question_t * qs, int len) {
  int creat_sum = 0;
  int solv_sum = qs[0].create_time;
  int i = 0;
  for (; i < len; i++) {
    //printf("[%d] creat_sum %d, solv_sum %d\n", i, creat_sum,
    //       solv_sum);
    creat_sum += qs[i].create_time;
    if (creat_sum > solv_sum) {
      //printf("[%d] creat_sum %d, solv_sum %d\n", i, creat_sum,
      //       solv_sum);
      solv_sum += creat_sum - solv_sum;
    }
    solv_sum += qs[i].solve_time;
  }
  return solv_sum; 
}

question_t *
create_questions(int len) {
  return calloc(len, sizeof(question_t));
}

int
main(void) {
  int qs_len;
  while (scanf("%d", &qs_len) == 1) {
    question_t * qs = create_questions(qs_len);
    int i = 0;
    for (; i < qs_len; i++) {
      scanf("%d%d", &qs[i].create_time, &qs[i].solve_time);
    }
    sort_questions(qs, qs_len);
    i = 0;
    for (; i < qs_len; i++) {
      //printf("%d %d\n", qs[i].create_time, qs[i].solve_time);
    }
    int min = min_questions_solve_time(qs, qs_len);
    printf("%d\n", min);
    free(qs);
  }
  return 0;
}
