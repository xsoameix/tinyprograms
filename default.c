#include <stdio.h>

int
main(void) {
    int a = 1;
    int b = a ? a : 2;
    printf("b: %d\n", b);
    a = 0;
    b = a ? a : 2;
    printf("b: %d\n", b);
    return 0;
}
