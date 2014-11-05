#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

typedef uint8_t utf_t;

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

static int8_t trans[][256] = {
  { // state 0
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
    /* A */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* B */ F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
    /* C */ F, F, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    /* D */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    /* E */ 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3,
    /* F */ 5, 6, 6, 6, 7, F, F, F, F, F, F, F, F, F, F, F
  },
  { // state 1
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
  { // state 2
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
  { // state 3
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
  { // state 4
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
  { // state 5
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
  { // state 6
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
  { // state 7
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
utf8_len(utf_t * c) {
  size_t len = 0;
  size_t state = 0;
  while (1) {
    state = trans[state][* c];
    c += 1;
    len += 1;
    switch (state) {
      case ACCEPT:
        return len;
      case FAILURE:
        return 0;
    }
  };
}

typedef uint32_t ucode_t;

#define BIT_MASK(n) (1 << (n) - 1)

static ucode_t
utf8_code(utf_t * c) {
  ucode_t code = * c;
  size_t len = utf8_len(c);
  if (len > 1) {
    c++;
    len--;
    code = * c & BIT_MASK(6 - len);
    while (len--) {
      c++;
      code <<= 6;
      code |= * c & BIT_MASK(6);
    }
  }
  return code;
}

FILE *
file_open(int files_len, utf_t * filename) {
  if (files_len != 1) {
    puts("should input 1 file");
    exit(0);
  }
  FILE * file = fopen(filename, "r");
  if (file == NULL) {
    printf("no %s file\n", filename);
    exit(0);
  }
  return file;
}

typedef void fread_t(utf_t * file, size_t size);

void
file_read(int files_len, utf_t * filename, fread_t * yield) {
  FILE * file = file_open(files_len, filename);
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);
  utf_t * buf = malloc(size);
  if (buf == NULL) {
    printf("alloc memory error for file %s\n", filename);
    exit(0);
  }
  size_t read_size = fread(buf, 1, size, file);
  if (read_size != size) {
    printf("reading error for file %s\n", filename);
    exit(0);
  }
  fclose(file);
  yield(buf, size);
  free(buf);
}

void
scan_source(utf_t * string, size_t size) {
  size_t i = 0;
  while (i < size) {
    utf_t * str = &string[i];
    size_t len = utf8_len(str);
    if (strncmp(str, "․", len) == 0) {
      printf("->_->");
    } else {
      utf_t buf[4];
      strncpy(buf, str, len);
      buf[len] = '\0';
      printf("%s", buf);
    }
    i += len;
  }
}

typedef struct {
  size_t len;
  ucode_t code;
  utf_t * c;
} uchar_t;

typedef enum {
  UNKNOWN,

  CLASS,    // class
  EXTENDS,  // <
  LBLOCK,   // {
  RBLOCK,   // }
  STRUCT,   // struct
  METHODS,  // methods
  TERM,     // [\r\n\s]+

  SELF,     // self
  ID,       // [a-zA-Z_]+
  OVERRIDE, // =
  STAT,     // ;
  OTHERS    // .*
} def_t;

typedef struct {
  def_t def;
  size_t len;
  utf_t * string;
} tok_t;

typedef struct scan {
  size_t i;
  size_t size;
  utf_t * string;
  tok_t (* scan_tok)(struct scan * scan);
} scan_t;

typedef struct {
  ucode_t cmp;
  ucode_t * period;
} dfa_t;

int
scan_is(ucode_t code, dfa_t * dfa) {
  size_t i = 0;
  while (1) {
    dfa_t * node = &dfa[i];
    if (node->period == NULL) {
      i *= 2;
      i += (code <= node->cmp) ? 1 : 2;
    } else {
      return (code >= node->period[0] &&
              code <= node->period[1]);
    }
  }
}

#define lenof(ary) (sizeof(ary) / sizeof(ary[0]))

uchar_t
scan_char(scan_t * scan) {
  utf_t * string = scan->string;
  size_t i = scan->i;
  size_t size = scan->size;
  if (i >= size) return (uchar_t) {0};
  utf_t * str = &string[i];
  size_t len = utf8_len(str);
  ucode_t code = utf8_code(str);
  return (uchar_t) {len, code, str};
}

typedef enum {
  START,
  CLASS1,
  CLASS2,
  CLASS3,
  CLASS4,
  CLASS5,
  METHODS1,
  METHODS2,
  METHODS3,
  METHODS4,
  METHODS5,
  METHODS6,
  METHODS7,
  STRUCT1,
  STRUCT2,
  STRUCT3,
  STRUCT4,
  STRUCT5,
  STRUCT6,
  EXTENDS1,
  LBLOCK1,
  RBLOCK1,
  ID1,
  TERM1,

  SELF1,
  SELF2,
  SELF3,
  SELF4,
  OVERRIDE1,
  STAT1,
  OTHERS1
} state_t;

void
scan_perror(ucode_t code) {
  printf("not allowed char %" PRIu32 "\n", code);
  exit(0);
}

#define UCMP(cmp) {cmp, 0}
#define UPERIOD(begin, end) {0, (ucode_t[]) {begin, end}}

static dfa_t did1[] = {
  UCMP('l'),

  UCMP('_'),
  UCMP('r'),

  UCMP('Z'),
  UCMP('b'),
  UPERIOD('n', 'r'),
  UPERIOD('t', 'z'),

  UPERIOD('A', 'Z'),
  UPERIOD('_', '_'),
  UPERIOD('a', 'b'),
  UPERIOD('d', 'l')
};

static dfa_t did2[] = {
  UCMP('_'),

  UCMP('Z'),
  UPERIOD('a', 'z'),

  UPERIOD('A', 'Z'),
  UPERIOD('_', '_')
};

#define UNOT(code) { \
    UCMP('_'), \
    \
    UCMP('Z'), \
    UCMP(code - 1), \
    \
    UPERIOD('A', 'Z'), \
    UPERIOD('_', '_'), \
    UPERIOD('a', code - 1), \
    UPERIOD(code + 1, 'z') \
  }

static dfa_t dclass1[] = UNOT('l');
static dfa_t dclass2[] = UNOT('a');
static dfa_t dclass3[] = UNOT('s');
static dfa_t dmethods1[] = UNOT('e');
static dfa_t dmethods2[] = UNOT('t');
static dfa_t dmethods3[] = UNOT('h');
static dfa_t dmethods4[] = UNOT('o');
static dfa_t dmethods5[] = UNOT('d');
static dfa_t * dmethods6 = dclass3;
static dfa_t * dstruct1 = dmethods2;
static dfa_t dstruct2[] = UNOT('r');
static dfa_t dstruct3[] = UNOT('u');
static dfa_t dstruct4[] = UNOT('c');
static dfa_t * dstruct5 = dmethods2;

static dfa_t dterm1[] = {
  UCMP(0x0D),

  UCMP(0x0A),
  UPERIOD(0x20, 0x20),

  UPERIOD(0x0A, 0x0A),
  UPERIOD(0x0D, 0x0D)
};

#define SCAN_KEYWORD(ucode, next_state, not) \
  if (c == ucode) { \
    state = next_state; \
  } else if (scan_is(code, not)) { \
    state = ID1; \
  } else { \
    state = OTHERS; \
    break; \
  }
#define SCAN_KEYWORD_END(definition) \
  if (scan_is(code, did2)) { \
    state = ID1; \
  } else { \
    def = definition; \
    break; \
  }

tok_t
scan_token(scan_t * scan) {
  def_t def = UNKNOWN;
  state_t state = START;
  uchar_t uchar = scan_char(scan);
  size_t i = scan->i;
  while (scan->i < scan->size) {
    ucode_t code = uchar.code;
    utf_t c = * uchar.c;

    //utf_t buf[64];
    //size_t buflen = uchar.len;
    //if (buflen >= lenof(buf)) buflen = lenof(buf) - 1;
    //strncpy(buf, uchar.c, buflen);
    //buf[buflen] = '\0';

    //printf("state %d, scan [%s]\n", state, buf);
    if (state == START) {
      if (c == 'c') {
        state = CLASS1;
      } else if (c == 'm') {
        state = METHODS1;
      } else if (c == 's') {
        state = STRUCT1;
      } else if (c == '<') {
        state = EXTENDS1;
      } else if (c == '{') {
        state = LBLOCK1;
      } else if (c == '}') {
        state = RBLOCK1;
      } else if (scan_is(code, dterm1)) {
        state = TERM1;
      } else if (scan_is(code, did1)) {
        state = ID1;
      } else {
        break;
      }
    } else if (state == CLASS1) {
      SCAN_KEYWORD('l', CLASS2, dclass1)
    } else if (state == CLASS2) {
      SCAN_KEYWORD('a', CLASS3, dclass2)
    } else if (state == CLASS3) {
      SCAN_KEYWORD('s', CLASS4, dclass3)
    } else if (state == CLASS4) {
      SCAN_KEYWORD('s', CLASS5, dclass3)
    } else if (state == CLASS5) {
      SCAN_KEYWORD_END(CLASS)
    } else if (state == STRUCT1) {
      SCAN_KEYWORD('t', STRUCT2, dstruct1)
    } else if (state == STRUCT2) {
      SCAN_KEYWORD('r', STRUCT3, dstruct2)
    } else if (state == STRUCT3) {
      SCAN_KEYWORD('u', STRUCT4, dstruct3)
    } else if (state == STRUCT4) {
      SCAN_KEYWORD('c', STRUCT5, dstruct4)
    } else if (state == STRUCT5) {
      SCAN_KEYWORD('t', STRUCT6, dstruct5)
    } else if (state == STRUCT6) {
      SCAN_KEYWORD_END(STRUCT)
    } else if (state == METHODS1) {
      SCAN_KEYWORD('e', METHODS2, dmethods1)
    } else if (state == METHODS2) {
      SCAN_KEYWORD('t', METHODS3, dmethods2)
    } else if (state == METHODS3) {
      SCAN_KEYWORD('h', METHODS4, dmethods3)
    } else if (state == METHODS4) {
      SCAN_KEYWORD('o', METHODS5, dmethods4)
    } else if (state == METHODS5) {
      SCAN_KEYWORD('d', METHODS6, dmethods5)
    } else if (state == METHODS6) {
      SCAN_KEYWORD('s', METHODS7, dmethods6)
    } else if (state == METHODS7) {
      SCAN_KEYWORD_END(METHODS)
    } else if (state == EXTENDS1) {
      def = EXTENDS;
      break;
    } else if (state == LBLOCK1) {
      def = LBLOCK;
      break;
    } else if (state == RBLOCK1) {
      def = RBLOCK;
      break;
    } else if (state == TERM1) {
      if (scan_is(code, dterm1)) {
        state = TERM1;
      } else {
        def = TERM;
        break;
      }
    } else if (state == ID1) {
      if (scan_is(code, did2)) {
        state = ID1;
      } else {
        def = ID;
        break;
      }
    } else {
    }
    scan->i += uchar.len;
    uchar = scan_char(scan);
  }
  size_t len = scan->i - i;
  utf_t * string = &scan->string[i];
  return (tok_t) {def, len, string};
}

#undef SCAN_KEYWORD
#define SCAN_KEYWORD(ucode, next_state) \
  if (c == ucode) { \
    state = next_state; \
  } else { \
    state = OTHERS1; \
    break; \
  }
#undef SCAN_KEYWORD_END
#define SCAN_KEYWORD_END(definition) \
  def = definition; \
  break;

tok_t
scan_ctoken(scan_t * scan) {
  def_t def = UNKNOWN;
  state_t state = START;
  uchar_t uchar = scan_char(scan);
  size_t i = scan->i;
  static int stop = 0;
  while (scan->i < scan->size) {
    if (stop++ == 455) break;
    ucode_t code = uchar.code;
    utf_t c = * uchar.c;
    //printf("state %d\n", state);
    if (state == START) {
      if (c == 's') {
        state = SELF1;
      } else if (c == '}') {
        state = RBLOCK1;
      } else if (c == '!') {
        state = OVERRIDE1;
      } else if (c == ';') {
        state = STAT1;
      } else {
        state = OTHERS1;
      }
    } else if (state == SELF1) {
      SCAN_KEYWORD('e', SELF2)
    } else if (state == SELF2) {
      SCAN_KEYWORD('l', SELF3)
    } else if (state == SELF3) {
      SCAN_KEYWORD('f', SELF4)
    } else if (state == SELF4) {
      SCAN_KEYWORD_END(SELF)
    } else if (state == RBLOCK1) {
      def = RBLOCK;
      break;
    } else if (state == STAT1) {
      def = STAT;
      break;
    } else if (state == OVERRIDE1) {
      if (scan_is(code, did2)) {
        state = OVERRIDE1;
      } else {
        def = OVERRIDE;
        break;
      }
    } else if (state == OTHERS1) {
      def = OTHERS;
      break;
    } else {
    }
    scan->i += uchar.len;
    uchar = scan_char(scan);
  }
  size_t len = scan->i - i;
  utf_t * string = &scan->string[i];
  return (tok_t) {def, len, string};
}

scan_t
scan_new(utf_t * string, size_t size) {
  return (scan_t) {0, size, string, scan_token};
}

tok_t
parse_next(scan_t * scan) {
  tok_t tok = scan->scan_tok(scan);
  utf_t buf[64];
  size_t len = tok.len;
  if (len >= lenof(buf)) len = lenof(buf) - 1;
  utf_t * str = tok.string;
  strncpy(buf, str, len);
  buf[len] = '\0';
  //printf("[%s]", buf);
  return tok;
}

int
parse_test(tok_t * tok, def_t def) {
  return tok->def == def;
}

void
parse_check(tok_t * tok, def_t def) {
  if (!parse_test(tok, def)) {
    printf("expected token %d, given %d\n", def, tok->def);
    exit(0);
  }
}

tok_t
parse_match(scan_t * scan, def_t def) {
  tok_t tok = parse_next(scan);
  parse_check(&tok, def);
  return tok;
}

// match with terminator
tok_t
parse_term(scan_t * scan, def_t def) {
  tok_t tok = parse_match(scan, def);
  parse_match(scan, TERM);
  return tok;
}

typedef struct {
  size_t len;
  size_t capa;
  void * objs;
} ary_t;

typedef union {
  struct {
    ary_t name;
  } nm; // normal
  struct {
    ary_t ret;
    tok_t name;
    ary_t arg;
  } or; // override
} meth_t;

typedef struct {
  tok_t class;
  tok_t super;
  tok_t strukt;
  ary_t meths;
  utf_t * header;
  utf_t * super_type;
  utf_t * class_type;
  utf_t * instance_type;
  utf_t * class_name;
  utf_t * instance_name;
  utf_t * class_prefix;
  utf_t * super_prefix;
  utf_t * methods_name;
  utf_t * instances_name;
  utf_t * super_methods_name;
  utf_t * super_instances_name;
  utf_t * init_name;
} class_t;

void
ary_new(ary_t * ary, size_t capa, size_t size) {
  if (ary->objs != 0) {
    printf("ary is already newed.\n");
    exit(0);
  }
  ary->capa = capa;
  ary->objs = calloc(capa, size);
}

void
ary_add(ary_t * ary, void * obj, size_t size) {
  if (ary->len >= ary->capa) {
    ary->capa *= 2;
    ary->objs = realloc(ary->objs, ary->capa * size);
  }
  memcpy(ary->objs + size * ary->len++, obj, size);
}

#define meth_new(class, capa) \
  ary_new(&(class)->meths, capa, sizeof(meth_t))

#define meth_add(class, meth) \
  ary_add(&(class)->meths, meth, sizeof(meth_t))

#define meth_get(class, i) \
  ((meth_t *) (class)->meths.objs)[i]

#define tok_get(toks, i) \
  ((tok_t *) (toks)->objs)[i]

#define tok_new(toks) \
  ary_new(toks, 1, sizeof(tok_t))

#define tok_add(toks, tok) \
  ary_add(toks, tok, sizeof(tok_t))

utf_t *
tok_str(tok_t * tok) {
  static utf_t buf[64] = {0};
  size_t len = tok->len;
  if (len >= lenof(buf)) len = lenof(buf) - 1;
  strncpy(buf, tok->string, len);
  buf[len] = '\0';
  return buf;
}

void
toks_print(ary_t * toks) {
  printf("[");
  size_t i = 0;
  for (; i < toks->len; i++) {
    printf("%s", tok_str(&tok_get(toks, i)));
  }
  printf("]");
}

void
meth_del(class_t * class) {
  size_t len = class->meths.len;
  size_t i = 0;
  for (; i < len; i++) {
    meth_t * meth = &meth_get(class, i);
    if (meth->or.name.string == NULL) {
      free(meth->nm.name.objs);
    } else {
      free(meth->or.ret.objs);
      free(meth->or.arg.objs);
    }
  }
  free(class->meths.objs);
}

class_t
parse_header(utf_t * string, size_t size) {
  scan_t scan = scan_new(string, size);
  parse_term(&scan, CLASS);
  class_t class = {0};
  class.class = parse_term(&scan, ID);
  parse_term(&scan, EXTENDS);
  class.super = parse_term(&scan, ID);
  parse_term(&scan, LBLOCK);
  parse_term(&scan, STRUCT);
  parse_match(&scan, LBLOCK);
  scan.scan_tok = scan_ctoken;
  tok_t tok = parse_next(&scan);
  class.strukt = tok;
  class.strukt.len = 0;
  while (!parse_test(&tok, RBLOCK)) {
    class.strukt.len += tok.len;
    tok = parse_next(&scan);
  }
  scan.scan_tok = scan_token;
  parse_match(&scan, TERM);
  parse_term(&scan, METHODS);
  parse_match(&scan, LBLOCK);
  scan.scan_tok = scan_ctoken;
  meth_t meth = {0};
  meth_new(&class, 4);
  while (1) {
    tok_t tok = parse_next(&scan);
    if (parse_test(&tok, RBLOCK)) {
      break;
    } else if (parse_test(&tok, OVERRIDE)) {
      meth.or.name = tok;
    } else if (parse_test(&tok, STAT)) {
      meth_add(&class, &meth);
      meth = (meth_t) {0};
    } else {
      if (meth.nm.name.objs == NULL) {
        tok_new(&meth.nm.name);
        tok_add(&meth.nm.name, &tok);
      } else if (meth.or.name.string == NULL) {
        tok_add(&meth.or.ret, &tok);
      } else if (meth.or.arg.objs == NULL) {
        tok_new(&meth.or.arg);
        tok_add(&meth.or.arg, &tok);
      } else {
        tok_add(&meth.or.arg, &tok);
      }
    }
  }
  free(meth.nm.name.objs);
  scan.scan_tok = scan_token;
  parse_match(&scan, TERM);
  parse_match(&scan, RBLOCK);
  puts("");
  return class;
}

int
str_is_upcase(utf_t c) {
  return c >= 'A' && c <= 'Z';
}

int
str_is_dwcase(utf_t c) {
  return c >= 'a' && c <= 'z';
}

size_t
tok_word(utf_t * string, size_t len) {
  size_t upwords = 0;
  size_t i = 0;
  size_t prev = i;
  while (i < len) {
    utf_t * str = &string[i];
    size_t len = utf8_len(str);
    if (!(len == 1 &&
          str_is_upcase(* str))) {
      break;
    }
    prev = i;
    i += len;
    upwords++;
  }
  if (upwords <= 1) {
    while (i < len) {
      utf_t * str = &string[i];
      size_t len = utf8_len(str);
      if (len == 1 &&
          str_is_upcase(* str)) {
        break;
      }
      i += len;
    }
  } else {
    i = prev;
  }
  return i;
}

size_t
tok_words(tok_t * tok) {
  size_t words = 0;
  size_t i = 0;
  while (i < tok->len) {
    utf_t * str = &tok->string[i];
    size_t len = utf8_len(str);
    size_t wlen = tok_word(str, tok->len - i);
    if (wlen) {
      words++;
      i += wlen;
    } else {
      i += len;
    }
  }
  if (words == 0) words = 1;
  return words;
}

typedef int str_is_case_t(utf_t c);
typedef utf_t str_case_t(utf_t c);

utf_t
str_upcase(utf_t c) {
  return c - 0x20;
}

utf_t
str_dwcase(utf_t c) {
  return c + 0x20;
}

void
tok_case(utf_t * dest, utf_t * src, size_t len,
         str_is_case_t * cmp, str_case_t * yield) {
  size_t i = 0;
  while (i < len) {
    utf_t * str = &src[i];
    size_t len = utf8_len(str);
    strncpy(&dest[i], str, len);
    if (len == 1 &&
        cmp(* str)) {
      dest[i] = yield(* str);
    }
    i += len;
  }
}

void
tok_upcase(utf_t * dest, utf_t * src, size_t len) {
  tok_case(dest, src, len, str_is_dwcase, str_upcase);
}

void
tok_dwcase(utf_t * dest, utf_t * src, size_t len) {
  tok_case(dest, src, len, str_is_upcase, str_dwcase);
}

typedef void tok_case_t(utf_t * dest, utf_t * src, size_t len);

void
tok_inflect(utf_t * dest, tok_t * src, tok_case_t * yield) {
  size_t i = 0;
  while (i < src->len) {
    utf_t * str = &src->string[i];
    size_t len = utf8_len(str);
    size_t wlen = tok_word(str, src->len - i);
    printf("%c wlen %zu\n", * str, wlen);
    if (wlen) {
      yield(dest, str, wlen);
      i += wlen;
      dest += wlen;
      * dest++ = '_';
    } else {
      strncpy(dest, str, len);
      i += len;
      dest += len;
    }
  }
}

// FooBar => FOO_BAR
void
tok_constantize(utf_t * dest, tok_t * src) {
  tok_inflect(dest, src, tok_upcase);
}

// FooBar => foo_bar
void
tok_underscore(utf_t * dest, tok_t * src) {
  tok_inflect(dest, src, tok_dwcase);
}

typedef void tok_inflect_t(utf_t * dest, tok_t * src);

utf_t *
class_prefix(tok_t * src, utf_t * prefix, utf_t * suffix,
             tok_inflect_t * yield) {
  size_t plen = strlen(prefix);
  size_t slen = strlen(suffix);
  size_t len = (plen + src->len + tok_words(src) - 1 +
                slen + 1);
  utf_t * dest = malloc(len);
  printf("words %zu\n", tok_words(src));
  printf("len %zu\n", len);
  strncpy(dest, prefix, plen);
  yield(dest + plen, src);
  strncpy(dest + len - slen - 1, suffix, slen);
  dest[len - 1] = '\0';
  return dest;
}

// FooBar  > O_FOO_BAR_H
// FooBar  > o_class_foo_bar_t
// FooBar  > o_foo_bar_t
// FooBar => o_class_foo_bar
// FooBar => o_foo_bar
// FooBar  > o_class_foo_bar_
// FooBar => o_class_foo_bar_methods
// FooBar => o_foo_bar_instance_variables
// FooBar => o_init_foo_bar_class
void
class_types(class_t * class) {
  tok_t * klass = &class->class;
  tok_t * super = &class->super;
  class->header = class_prefix(klass, "O_", "_H", tok_constantize);
  class->class_type = class_prefix(klass, "o_class_", "_t", tok_underscore);
  class->super_type = class_prefix(super, "o_class_", "_t", tok_underscore);
  class->instance_type = class_prefix(klass, "o_", "_t", tok_underscore);
  class->class_name = class_prefix(klass, "o_class_", "", tok_underscore);
  class->instance_name = class_prefix(klass, "o_", "", tok_underscore);
  class->class_prefix = class_prefix(klass, "o_class_", "_", tok_underscore);
  class->super_prefix = class_prefix(super, "o_class_", "_", tok_underscore);
  class->methods_name = class_prefix(klass, "o_class_", "_methods",
                                     tok_underscore);
  class->instances_name = class_prefix(klass, "o_", "_instance_variables",
                                       tok_underscore);
  class->super_methods_name = class_prefix(super, "o_class_", "_methods",
                                           tok_underscore);
  class->super_instances_name = class_prefix(super, "o_", "_instance_variables",
                                             tok_underscore);
  class->init_name = class_prefix(klass, "o_init_", "_class", tok_underscore);
}

void
build_header(utf_t * string, size_t size) {
  class_t class = parse_header(string, size);
  printf("class: [%s]\n", tok_str(&class.class));
  printf("super: [%s]\n", tok_str(&class.super));
  printf("struct: [%s]\n", tok_str(&class.strukt));
  printf("method[%zu]:\n", class.meths.len);
  size_t i = 0;
  for (; i < class.meths.len; i++) {
    meth_t * meth = &((meth_t *) class.meths.objs)[i];
    if (meth->or.name.string == NULL) {
      toks_print(&meth->nm.name);
    } else {
      toks_print(&meth->or.ret);
      printf("[%s]", tok_str(&meth->or.name));
      toks_print(&meth->or.arg);
    }
  }
  puts("");
  class_types(&class);
  printf("class header: %s\n", class.header);
  printf("class class_type: %s\n", class.class_type);
  printf("class.super_type: %s\n", class.super_type);
  printf("class.instance_type: %s\n", class.instance_type);
  printf("class.class_name: %s\n", class.class_name);
  printf("class.instance_name: %s\n", class.instance_name);
  printf("class.class_prefix: %s\n", class.class_prefix);
  printf("class.super_prefix: %s\n", class.super_prefix);
  printf("class.methods_name: %s\n", class.methods_name);
  printf("class.instances_name: %s\n", class.instances_name);
  printf("class.super_methods_name: %s\n", class.super_methods_name);
  printf("class.super_instances_name: %s\n", class.super_instances_name);
  printf("class.init_name: %s\n", class.init_name);
  free(class.header);
  free(class.class_type);
  meth_del(&class);
}

typedef enum {
  SOURCE,
  HEADER,
  NOP
} action;

action
scan_args(int argc, utf_t ** argv) {
  if (argc <= 1) {
    puts("no input");
    exit(0);
  }
  if (argc == 2) {
    return SOURCE;
  }
  if (argc == 3 &&
      strcmp(argv[1], "-h") == 0) {
    return HEADER;
  }
  return NOP;
}

int
main(int argc, utf_t ** argv) {
  action act = scan_args(argc, argv);
  if (act == SOURCE) {
    file_read(argc - 1, argv[1], scan_source);
  }
  if (act == HEADER) {
    file_read(argc - 2, argv[2], build_header);
  }
  return 0;
}
