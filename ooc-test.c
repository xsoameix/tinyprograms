#include <libooc/string.conflict.h>

int
main(void) {
    string_init();
    void * string = new(String, "hello world");
    string_puts(string);
    delete(string);
    return 0;
}
