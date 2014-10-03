struct la {
    int a;
    int b;
};
int main(void) {
    struct la a = {5, 10};
    struct la * b = &a;
    int c = b->a;
    return 0;
}
