#ifndef CIRCLE_STRCUT_H
#define CIRCLE_STRCUT_H

// get the parent's struct definition
#include <libooc/object.struct.h>
// declare the methods
#include "circle.h"

struct Circle {
    struct Object super;
    int radius;
};

// declare virtual table(like C++) of Circle
O_DEF_CLASS_STRUCT()

#endif
