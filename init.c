#define M1(x) x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x
#define M2(x) M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x), M1(x)
#define M3(x) M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x), M2(x)
#define M4(x) M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x), M3(x)
#define M5(x) M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x), M4(x)
#define M6(x) M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x), M5(x)
static char t[1024] = {M6(1)};
int
main(void) {
  return 0;
}
