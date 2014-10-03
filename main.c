#include <stdio.h>
#include <libooc/object_type.h>
#include "circle.h"

int
main(void) {
    o circle = new(Circle, 2);
    int area = Circle_area(circle);
    printf("circle area: %d\n", area);
    delete(circle);
    return 0;
}
