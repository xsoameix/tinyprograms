#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

int
ary_homogeneous_len(uint32_t * ary, int len) {
  int max_i = 0;
  int i = 1;
  for (; i < len; i++) {
    if (ary[i] > ary[max_i]) {
      max_i = i;
    } else {
      break;
    }
  }
  return max_i + 1;
}

uint32_t
min(uint32_t a, uint32_t b) {
  return a < b ? a : b;
}

int *
create_ary(int len) {
  static uint32_t ary_storage[100000];
  memset(ary_storage, 0, 100000);
  return ary_storage;
  //return calloc(len, sizeof(int));
}

int
main(void) {
  int len;
  scanf("%d", &len);
  int i = 0;
  for (; i < len; i++) {
    int students_len;
    scanf("%d", &students_len);
    uint32_t * students = create_ary(students_len);
    int student_i = 0;
    for (; student_i < students_len; student_i++) {
      scanf("%d", &students[student_i]);
    }
    int len = ary_homogeneous_len(students, students_len);
    printf("%d\n", min(students[0], students[len]));
    //free(students);
  }
  return 0;
}
