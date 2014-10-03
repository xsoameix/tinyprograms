#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

struct Object {
    struct Class * class;
};

struct Class {
    char * name;
    struct Class * super;
    int size;
};

struct Class Object = {
    "Object", 0,
    sizeof(struct Object)
};
struct Class Class = {
    "Class", &Object,
    sizeof(struct Class)
};

struct Point {
    struct Class * class;
    int x;
    int y;
};

struct PointClass {
};

void *
Point_new(struct Class class) {
}

void *
new(void * class, va_list * args) {
    struct Object * object = malloc(Class->size);
    char * name = va_arg(* args, char *);
    object->super = va_arg(* args, 
    return object;
}

int main(void) {
    printf("name of Class:  %s\n", Class.name);
    printf("name of Object: %s\n", Object.name);
    printf("superclass name of Class:  %s\n", Class.super->name);
    void * PointClass = new(Class, Object, sizeof(struct PointClass)
    void * Point = new(PointClass, Object, sizeof(struct Point)
    return 0;
}
