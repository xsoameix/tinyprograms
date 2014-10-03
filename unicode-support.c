#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <libooc/string.conflict.h>
#include <libooc/file.h>

// gcc -std=gnu99 -I. -I.. -I/usr/local/include/libooc-0.0.1 -g -O0 -c % && gcc -std=gnu99 -g -O0 -o %:r %:r.o -L/usr/local/lib -looc-0.0.1

static void
init(void) {
    String_init();
    File_init();
}

//                                  0zzz zzzz
//                                   000 0000 (     0) to
//                                   111 1111 (    7F)
//                       110y yyyy  10zz zzzz
//                          0 0010    00 0000 (    80) to
//                          1 1111    11 1111 (   7FF)
//            1110 xxxx  10yy yyyy  10zz zzzz
//                 0000    10 0000    00 0000 (   800) to
//                 0000    11 1111    11 1111 (   FFF)
//                 0001    00 0000    00 0000 (  1000) to
//                 1100    11 1111    11 1111 (  CFFF)
//                 1101    00 0000    00 0000 (  D000) to
//                 1101    01 1111    11 1111 (  D7FF)
//                 1110    00 0000    00 0000 (  E000) to
//                 1111    11 1111    11 1111 (  FFFF)
// 1111 0www  10xx xxxx  10yy yyyy  10zz zzzz
//       000    01 0000    00 0000    00 0000 ( 10000) to
//       000    11 1111    11 1111    11 1111 ( 1FFFF)
//       001    00 0000    00 0000    00 0000 ( 20000) to
//       011    11 1111    11 1111    11 1111 ( FFFFF)
//       100    00 0000    00 0000    00 0000 (100000) to
//       100    00 1111    11 1111    11 1111 (10FFFF)
//
// transition digram(state 0 to 7):
//                               0 [00-7F] (     0 to     7F)
//                     0 [C2-DF] 1 [80-BF] (    80 to    7FF)
//           0  E0     2 [A0-BF] 1 [80-BF] (   800 to    FFF)
//           0 [E1-EC] 3 [80-BF] 1 [80-BF] (  1000 to   CFFF)
//           0  ED     4 [80-9F] 1 [80-BF] (  D000 to   D7FF)
//           0 [EE-EF] 3 [80-BF] 1 [80-BF] (  E000 to   FFFF)
// 0  F0     5 [90-BF] 3 [80-BF] 1 [80-BF] ( 10000 to  1FFFF)
// 0 [F1-F3] 6 [80-BF] 3 [80-BF] 1 [80-BF] ( 20000 to  FFFFF)
// 0  F4     7 [80-8F] 3 [80-BF] 1 [80-BF] (100000 to 10FFFF)

enum state {
    ACCEPT = -2, // accept
    FAILURE      // failure
};

#define A ACCEPT
#define F FAILURE

static int trans[8][256] = {
    {   // state 0
        //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
        /* 0 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
        /* 1 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
        /* 2 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
        /* 3 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
        /* 4 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
        /* 5 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
        /* 6 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
        /* 7 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
        /* 8 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 9 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* B */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* C */ F, F, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        /* D */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        /* E */ 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3,
        /* F */ 5, 6, 6, 6, 7, F, F, F, F, F, F, F, F, F, F, F
    },
    {   // state 1
        //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
        /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 8 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
        /* 9 */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
        /* A */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
        /* B */ A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A,
        /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
    },
    {   // state 2
        //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
        /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 8 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 9 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* A */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        /* B */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
    },
    {   // state 3
        //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
        /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 8 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        /* 9 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        /* A */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        /* B */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
    },
    {   // state 4
        //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
        /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 8 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        /* 9 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        /* A */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* B */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
    },
    {   // state 5
        //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
        /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 8 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 9 */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        /* A */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        /* B */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
    },
    {   // state 6
        //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
        /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 8 */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        /* 9 */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        /* A */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        /* B */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
    },
    {   // state 7
        //      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
        /* 0 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 1 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 2 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 3 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 4 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 5 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 6 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 7 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* 8 */ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        /* 9 */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* A */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* B */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* C */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* D */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* E */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
        /* F */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F
    }
};

static size_t
utf8_char_len(uint8_t * p) {
    size_t len = 0;
    int state = 0;
    while(true) {
        printf("state %d, char %X\n", state, * p);
        state = trans[state][* p];
        p += 1;
        len += 1;
        switch(state) {
        case ACCEPT:
            return len;
        case FAILURE:
            return 0;
        }
    };
}

int
main(void) {
    init();
    void * input = new(File, "./utf8-example");
    void * content = File_read(input);
    uint8_t * string = Object_inspect(content);
    printf("[%s]\n", string);
    uint8_t buffer[30];
    buffer[0] = '\0';
    size_t len = strlen(string);
    size_t n;
    for(int i = 0; i < len; i += n) {
        n = utf8_char_len(string + i);
        strncpy(buffer, string + i, n);
        buffer[n] = '\0';
        printf("[%s]\n", buffer);
    }
    return 0;
}
