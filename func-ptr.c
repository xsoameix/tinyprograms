#include <stdio.h>

static void
add_one(char ** p) {
    *p += 1;
}

int
main(void) {
    char * s = "hello world";
    puts(s);
    add_one(&s);
    puts(s);
    return 0;
}
