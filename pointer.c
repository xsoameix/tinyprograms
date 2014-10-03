#include <stdio.h>

struct a {
    int *(*b)[2];
};

int main(void) {
    int arr[2] = {1,2};
    int * arr_1 = arr;
    int * arr_2 = arr + 1;
    int * arr_3[2] = {arr_1, arr_2};
    struct a la = {&arr_3};
    struct a * yo = &la;
    printf("%d\n", *(*yo->b)[1]);
    return 0;
}
