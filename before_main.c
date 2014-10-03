#include <stdio.h>

void before_main(void) __attribute__((constructor));

void
before_main(void) {
    puts("la");
}

int
main(void) {
    return 0;
}
