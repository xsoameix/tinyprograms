#ifndef O_CIRCLE_H
#define O_CIRCLE_H

#include <libooc/object.h>

// Please put included files here.


// Please put macros/type declarations here.


#undef O_CLASS
#undef O_PARENT
#define O_CLASS Circle
#define O_PARENT Object
#define O_Circle_OVERRIDE_METHODS_LEN 2
#define O_Circle_PUBLIC_METHODS_LEN 1
#define O_Circle_PRIVATE_METHODS_LEN 1
#define O_Circle_OVERRIDE_METHOD_0 ctor, void, (va_list * args, args)
#define O_Circle_OVERRIDE_METHOD_1 dtor, void
#define O_Circle_PUBLIC_METHOD_0 area, int
#define O_Circle_PRIVATE_METHOD_0 my_pow, int, (int base, base), (int exponent, exponent)
#define O_Circle_ctor O_Circle_OVERRIDE_METHOD_0
#define O_Circle_dtor O_Circle_OVERRIDE_METHOD_1
#define O_Circle_area O_Circle_PUBLIC_METHOD_0
#define O_Circle_my_pow O_Circle_PRIVATE_METHOD_0
O_DEF_GLOBAL_METHODS()

#endif
