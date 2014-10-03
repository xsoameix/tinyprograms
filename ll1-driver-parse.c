#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

// gcc -std=gnu99 -I. -I.. -I/usr/local/include/libooc-0.0.1 -g -O0 -c % && 
// gcc -std=gnu99 -g -O0 -o %:r %:r.o -L/usr/local/lib -looc-0.0.1

static int act[28][15] = {
    {-1,-1, 0,-1, 0,-1,-1,-1,-1,-1, 0,-1,-1,-1,-1},
    {-1,-1, 1,-1, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1, 3,-1,-1,-1,-1,-1,-1,-1,-1},
    { 5, 5,-1,-1,-1, 5, 4, 5, 5, 5,-1, 5, 5, 5, 5},
    {-1,-1, 7, 7, 7,-1,-1,-1,-1,-1, 6,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,-1,-1,-1,-1},
    {-1,10,-1,-1,10,-1,10,-1,-1,-1, 9,-1,-1,-1,10},
    {-1,-1,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,15,-1,-1,-1,-1,13,-1,-1,-1,-1,-1,-1,-1,14},
    {-1,18,-1,-1,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,17},
    {-1,-1,-1,-1,-1,19,-1,20,-1,-1,-1,20,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,21,-1,-1,-1,22,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,24,-1,23,-1,-1,-1,23,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,25,-1,-1,-1,26,-1,-1,-1,-1},
    {-1,29,-1,-1,-1,-1,27,-1,-1,-1,-1,-1,-1,-1,28},
    {31,33,-1,-1,-1,-1,-1,30,-1,-1,-1,30,-1,-1,32},
    {-1,-1,-1,-1,-1,-1,34,-1,-1,-1,35,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,38,-1,36,39,-1,-1,36,37,-1,-1},
    {-1,42,-1,-1,-1,-1,40,-1,-1,-1,-1,-1,-1,-1,41},
    {-1,-1,-1,-1,-1,-1,-1,43,-1,-1,-1,44,-1,-1,45},
    {-1,48,-1,-1,-1,-1,46,-1,-1,-1,-1,-1,-1,-1,47},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,49,-1,-1,50},
    {-1,-1,-1,-1,-1,-1,-1,52,-1,-1,-1,51,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,53,-1,-1,-1,54,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,55,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,57,-1,-1,-1,56,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,58,-1,-1,-1,-1,-1}
};

static int prhs[59] = {
    0,
    5,
    9,
    11,
    14,
    16,
    17,
    19,
    20,
    23,
    25,
    26,
    30,
    34,
    37,
    40,
    42,
    48,
    51,
    53,
    59,
    62,
    65,
    68,
    71,
    74,
    78,
    81,
    84,
    87,
    89,
    92,
    96,
    99,
    101,
    104,
    107,
    109,
    113,
    119,
    124,
    127,
    130,
    132,
    140,
    147,
    150,
    153,
    156,
    158,
    165,
    168,
    170,
    172,
    174,
    175,
    179,
    181,
    183
};

static int rhs[186] = {
     31,   4,   1,   4,  -1,
      8,   5,   7,  -1,
      8,  -1,
      3,  34,  -1,
      3,  34,  -1,
      4,  38,  -1,
      6,  38,  -1,
      6,  38,  -1,
     41,   2,  30,  -1,
      9,   5,  32,  -1,
     10,   2,  -1,
      9,  42,  -1,
     29,  -1,
     11,   2,  40,   2,  35,  -1,
      9,  42,  -1,
     29,  -1,
     12,  23,   2,   5,  25,  -1,
     12,  23,  -1,
     13,   2,  -1,
     15,   5,  -1,
     12,  23,  -1,
     14,  25,  -1,
     12,  23,   2,  -1,
     15,   5,  -1,
     16,   2,  -1,
     15,  42,  -1,
     29,  -1,
     17,  23,  -1,
     11,   2,  28,  -1,
     15,  42,  -1,
     29,  -1,
     18,   2,  -1,
     15,   5,  -1,
     13,  -1,
     11,   2,  40,  -1,
     19,   5,   9,   5,  33,  -1,
     21,   5,  24,  36,  -1,
     20,   2,  -1,
     19,  42,  -1,
     29,  -1,
     19,   5,   9,   5,  33,   2,  35,  -1,
     21,   5,  24,  36,   2,  39,  -1,
     19,  42,  -1,
     22,   2,  -1,
     21,  42,  -1,
     29,  -1,
     21,   5,  24,  36,   2,  39,  -1,
     21,  42,  -1,
     39,  -1,
     35,  -1,
     25,   2,  -1,
     27,  26,  33,  -1,
     38,  -1,
      2,  -1,
     29,  37,  -1
};

static char * map[] = {
    "start",
    "type_gmr",
    "s.",
    "s.'",
    "l.",
    "n.",
    "n.'",
    "looktype",
    "grammar",
    "1st_line",
    "1st_prod",
    "1st_blk",
    "nm_blk_nl",
    "nm_blk",
    "nm_nl",
    "nextline",
    "nextprod",
    "g_nm_b_nl",
    "g_nm_blk",
    "gmr_line",
    "gmr_lex",
    "lex_line",
    "lex",
    "name",
    "block?",
    "block",
    "delim",
    "code",
    "Or",
    "End",
    "LookType",
    "Eof",
    "Gmr",
    "Do",
    "Space",
    "GmrId",
    "regex",
    "Code",
    "Line",
    "LexId",
    "Colon",
    "CType",
    "Comment"
};

enum terminals {
    Or = 28,
    End,
    LookType,
    Eof,
    Gmr,
    Do,
    Space,
    GmrId,
    regex,
    Code,
    Line,
    LexId,
    Colon,
    CType,
    Comment
};

struct Token {
    int type;
    char * val;
};

static int token_i = 0;
static struct Token tokens[] = {
    {Line, "\\n"},
    {LookType, "lookahead_type"},
    {Space, "\\s"},
    {CType, "o_obj"},
    {Line, "\\n"},
    {Gmr, "grammar"},
    {Line, "\\n"},
    {Space, "\\s"},
    {GmrId, "start"},
    {Space, "\\s"},
    {Colon, ":"},
    {Space, "\\s"},
    {GmrId, "l."},
    {Space, "\\s"},
    {GmrId, "type_gmr"},
    {Space, "\\s"},
    {GmrId, "l."},
    {Space, "\\s"},
    {LexId, "EOF"},
    {Line, "\\n"},
    {Space, "\\s"},
    {LexId, "Gmr"},
    {Space, "\\s"},
    {regex, "/grammar/"},
    {Line, "\\n"},
    {End, "end"},
    {Line, "\\n"},
    {Eof, "Eof"}
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
        printf("look {%s}, top {%s}\n", map[look], map[top]);
        if(top < 28) {
            int action = act[top][look - 28];
            if(action == -1) {
                printf("1. syntax error\n");
                exit(0);
            }
            asp -= 1;
            int * symbol = &rhs[prhs[action]];
            printf("<< ");
            while(* symbol != -1) {
                printf("%s, ", map[* symbol]);
                * asp = * symbol;
                asp += 1;
                symbol += 1;
            }
            printf("\n");
        } else if(top > 42) {
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
