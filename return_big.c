struct bar {
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
};

struct bar
foo(void) {
    struct bar a = {1, 2, 3, 4, 5, 6};
    return a;
}

int
main(void) {
    struct bar a = foo();
    return 0;
}
