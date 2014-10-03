#include <stdio.h>

int
main(void) {
    char buf[BUFSIZ];
    setbuf(stderr, buf);
    fprintf(stderr, "LalalaError\n");
    fprintf(stderr, "Error\n");
    printf("%s", buf);
    return 0;
}
