#include <stdio.h>
#include <math.h>

typedef struct time {
  int hour;
  int minute;
} thetime_t;

int
main(void) {
  while (1) {
    thetime_t time;
    scanf("%d:%d\n", &time.hour, &time.minute);
    if (time.hour == 0 &&
        time.minute == 0) {
      break;
    }
    const double pi = 3.14;
    time.hour = time.hour == 12 ? 0 : time.hour;
    double hour_base_theta = time.hour * 2 * pi / 12;
    double minute_theta = time.minute * 2 * pi / 60;
    double hour_theta = hour_base_theta + minute_theta / 12;
    double offset = fabs(hour_theta - minute_theta) * 360 / (2 * pi);
    printf("%.3lf\n", offset > 180 ? 360 - offset : offset);
  }
  return 0;
}
