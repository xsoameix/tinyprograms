int all(void *, int (* itor)(void * x));
extern void * a;

int itor(void * x) { return isDone(x); }
void some(void) {
    int b = 1;
    all(a, itor);
}
