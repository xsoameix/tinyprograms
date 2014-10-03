#include <stdarg.h>

void
foo(va_list * args_ptr) {
    va_list args = {0};
    va_copy(args, * args_ptr);
    int a = 1;
}

void
bar(int a, ...) {
    va_list args;
    va_start(args, a);
}
