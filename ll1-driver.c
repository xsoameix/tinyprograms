#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

// gcc -std=gnu99 -I. -I.. -I/usr/local/include/libooc-0.0.1 -g -O0 -c % && 
// gcc -std=gnu99 -g -O0 -o ll1-driver ll1-driver.o -L/usr/local/lib -looc-0.0.1

static int act[6][6] = {
    {  0,  -1,  -1,  -1,   0,  -1},
    {  1,  -1,  -1,  -1,   1,  -1},
    { -1,   3,  -1,   2,  -1,   3},
    {  4,  -1,  -1,  -1,   4,  -1},
    { -1,   6,   5,   6,  -1,   6},
    {  7,  -1,  -1,  -1,   8,  -1}
};

static int prhs[9] = {
    0,
    3,
    6,
    10,
    11,
    14,
    17,
    18,
    22
};

static int rhs[24] = {
     11,   1,  -1,
      2,   3,  -1,
      2,  12,   3,   9,  -1,
      4,   5,  -1,
      4,   5,   8,  -1,
      7,   1,   6,  -1,
     10,  -1
};

//  6 (
//  7 )
//  8 *
//  9 +
// 10 digit
// 11 EOF

struct Token {
    int type;
    char * val;
};

static int token_i = 0;
static struct Token tokens[] = {
    {10, "1"},
    {9, "+"},
    {10, "2"},
    {11, "EOF"}
};

static struct Token token;

static int
scan(void) {
    token = tokens[token_i++];
    return token.type;
}

struct Expr {
    char * op;
    int a;
    int b;
};

static struct Expr *
new_Expr(char * op, int a, int b) {
    struct Expr * e = malloc(sizeof(struct Expr));
    e->op = op;
    e->a = a;
    e->b = b;
    return e;
}

static struct Token
driver(void) {
    struct Token vs[200];
    struct Token * vsp = vs;
    int as[200]; // action stack
    int * asp = as;
    * asp = 0;
    asp += 1;
    int look = scan();
    bool look_set = true;
    while(asp > as) {
        sleep(1);
        int top = * (asp - 1);
        printf("look %d, top %d\n", look, top);
        if(top < 6) {
            int action = act[top][look - 6];
            if(action == -1) {
                printf("1. syntax error\n");
                exit(0);
            }
            asp -= 1;
            int * symbol = &rhs[prhs[action]];
            printf("<< ");
            while(* symbol != -1) {
                printf("%d, ", * symbol);
                * asp = * symbol;
                asp += 1;
                symbol += 1;
            }
            printf("\n");
        } else if(top > 11) {
            switch(top) {
            case 12:
                {
                    // E* -> + T {
                    //         b = pop
                    //         op = pop
                    //         a = pop
                    //         push Expr.new op a b
                    //       } E*
                    //     | epsilon
                    //int b = (intptr_t) Array_pop(vs);
                    //int op = (intptr_t) Array_pop(vs);
                    //int a = (intptr_t) Array_pop(vs);
                    //Array_push(vs, new_Expr(op, a, b));
                    printf("vsp[top]: %s\n", (* (vsp - 1)).val);
                    printf("vsp[second]: %s\n", (* (vsp - 2)).val);
                    printf("vsp[third]: %s\n", (* (vsp - 3)).val);
                }
                break;
            default:
                break;
            }
            asp -= 1;
        } else if(look == top) {
            if(look_set) {
                * vsp = token;
                printf("match %s\n", (* vsp).val);
                vsp += 1;
                look_set = false;
            }
            asp -= 1;
            if(asp > as) {
                look = scan();
                look_set = true;
            }
        } else {
            printf("2. syntax error\n");
            exit(0);
        }
    }
    return * (vsp - 1);
}

int
main(void) {
    struct Token token = driver();
    printf("return: %s\n", token.val);
    return 0;
}
