struct big {
    int a;
    int b;
    int c;
    int d;
    int e;

    int f;
    int g;
    int h;
    int i;
    int j;

    int k;
    int l;
    int m;
    int n;
    int o;
};

struct object {
    struct big big;
    struct frame *frames;
};

struct frame {
    int a;
    int b;
    int hurtable;
};

extern struct object *b_object;
extern struct frame *frame_c;

int main(void) {
    struct frame frame_a = {33};
    struct frame frame_b = {44};
    struct frame frames[2] = {frame_a, frame_b};
    struct big a_big = {1,2,3,4,5,1,2,3,4,5,1,2,3,4,5};
    struct object a_object = {a_big, frames};
    b_object = &a_object;
    int frame_no = 1;
    frame_c = &(b_object->frames[frame_no]);
    int hurtable = frame_c->hurtable;
    return 0;
}
