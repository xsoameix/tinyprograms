#include <stdio.h>

int
main() {
    FILE * file;
    file = fopen("c-file", "w");
    if(file != NULL) {
        fputs("fopen example1", file);
        fputs("fopen example2", file);
        fclose(file);
    }
    return 0;
}
