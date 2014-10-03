#include <stdio.h>

void
Somefoo(void) {
    puts("Somefoo");
}

static void foo(void) {
    Somefoo();
}

int
main(void) {
    foo();
    return 0;
}
