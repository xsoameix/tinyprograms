#include <stdlib.h>

// struct definition of Circle
#include "circle.struct.h"

// inherit form Object
O_DEF_CLASS(Circle, Object)

// constructor
override
def(ctor, void : va_list * @args) {
    self->radius = va_arg(* args, int);
}

// destructor
override
def(dtor, void) {
    free(self);
}

// public method

def(area, int) {
    // call private method
    return my_pow(self, self->radius, 2);
}

// private method
private
def(my_pow, int : int @base . int @exponent) {
    int result = 1;
    while(exponent > 0) {
        result *= base;
        exponent -= 1;
    }
    return result;
}
