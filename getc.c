#include <stdio.h>

int
main(void) {
    char c = getc(stdin);
    while(c != '\n') {
        printf("%c\n", c);
        c = getc(stdin);
    }
    printf("last: [%c]", c);
    return 0;
}
