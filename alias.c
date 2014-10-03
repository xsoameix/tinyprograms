#include <stdio.h>

//__attribute__ ((weakref)) int lala(void);
static int lala(void) __attribute__ ((weakref, alias("la")));

int
main(void) {
    yo();
    printf("%d\n", lala());
    return 0;
}
