#include <string.h>

int
main(void) {
    char c[] = "123";
    c[0] = '\0';
    strncat(c, "ab", 1);
    puts(c);
    return 0;
}
