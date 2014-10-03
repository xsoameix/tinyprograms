#define EACH(ary, name) \
    void itor ## name(void)

int
main(void) {
    EACH(ary, item) {
    }
    return 0;
}
