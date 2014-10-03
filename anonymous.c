#include <stddef.h>

struct a {
    size_t a;
    struct {
        size_t b;
    } * b;
};

int
main(void) {
    struct a a = {1, NULL};
    void ** b = (void **) a.b;
    void * c = b[1];
    return 0;
}
