#include <stdio.h>

struct animal {
    struct animal_vtable_ *vtable_;
    char *name;
};

struct animal_vtable_ {
    char *(*sound)(void);
    int (*height)(void);
};

char *animal_sound(struct animal *animal) {
    return animal->vtable_->sound();
}

int animal_height(struct animal *animal) {
    return animal->vtable_->height();
}

char *sound(void) {
    return "meow!";
}

int height(void) {
    return 5;
}

char *bad_sound(void) {
    return "GAAAAAAAAAAAAAAAA!";
}

struct animal_vtable_ CAT[] = {{bad_sound, height}};

int main(void) {
    struct animal kitty = { &CAT[0], "Kitty" };

    printf("%s says %s\nheight is %d",
            kitty.name, animal_sound(&kitty),
            animal_height(&kitty));

    return 0;
}
