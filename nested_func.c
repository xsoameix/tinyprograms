#include <stdio.h>

typedef int (* func)(int);

static
inner(func f, int arg) {
    printf("%d\n", f(arg + 1));
}

static func
f(int arg) {
    int nested(int nested_arg) {
        return arg + nested_arg;
    }
    inner(nested, arg);
}

int
main(void) {
    f(1);
    return 0;
}
