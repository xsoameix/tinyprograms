int
is_punct(char c) {
    return c > 0x21 && c < 0x2F;
}

int
main(void) {
    char c = 'a';
    is_punct(c);
    return 0;
}
