#include <stdio.h>

int
main(void) {
  while (1) {
    int len, round;
    scanf("%d%d", &len, &round);
    if (len == 0 && round == 0) break;
    int i = 2;
    int live = 0;
    for (; i <= len; i++) {
      live += round;
      live %= i;
    }
    printf("%d\n", live + 1);
  }
  return 0;
}
