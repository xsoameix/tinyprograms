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

typedef void * fread_t(utf_t * file, size_t size);

void *
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
  void * ret = yield(buf, size);
  free(buf);
  return ret;
}

void *
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
  METHOD,   // -
  STAT,     // ;
  TSELF,    // @
  TCLASS,   // @@
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
  size_t eof;
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
  if (i >= size) {
    if (scan->eof) {
      printf("read end of file %zu\n", size);
      exit(0);
    } else {
      scan->eof = 1;
    }
    return (uchar_t) {0};
  }
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
  METHOD1,
  STAT1,
  TSELF1,
  TCLASS1,
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
      } else if (c == '{') {
        state = LBLOCK1;
      } else if (c == '}') {
        state = RBLOCK1;
      } else if (c == '-') {
        state = METHOD1;
      } else if (c == ';') {
        state = STAT1;
      } else if (c == '@') {
        state = TSELF1;
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
    } else if (state == LBLOCK1) {
      def = LBLOCK;
      break;
    } else if (state == RBLOCK1) {
      def = RBLOCK;
      break;
    } else if (state == STAT1) {
      def = STAT;
      break;
    } else if (state == TSELF1) {
      if (c == '@') {
        state = TCLASS1;
      } else {
        def = TSELF;
        break;
      }
    } else if (state == TCLASS1) {
      def = TCLASS;
      break;
    } else if (state == METHOD1) {
      if (scan_is(code, did2)) {
        state = METHOD1;
      } else {
        def = METHOD;
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
  utf_t * super_header;
  utf_t * super_type;
  utf_t * class_type;
  utf_t * instance_type;
  utf_t * class_name;
  utf_t * instance_name;
  utf_t * super_instance_name;
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
  &((meth_t *) (class)->meths.objs)[i]

#define tok_get(toks, i) \
  &((tok_t *) (toks)->objs)[i]

#define class_get(classes, i) \
  &((class_t *) (classes)->objs)[i]

#define tok_new(toks) \
  ary_new(toks, 1, sizeof(tok_t))

#define tok_add(toks, tok) \
  ary_add(toks, tok, sizeof(tok_t))

#define class_new(classes) \
  ary_new(classes, 2, sizeof(class_t))

#define class_add(classes, class) \
  ary_add(classes, class, sizeof(class_t))

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
toks_print(class_t * class, ary_t * toks) {
  size_t i = 0;
  for (; i < toks->len; i++) {
    tok_t * tok = tok_get(toks, i);
    def_t def = tok->def;
    if (def == TSELF) {
      printf("%s", class->instance_type);
    } else if (def == TCLASS) {
      printf("%s", class->class_type);
    } else if (def == SELF) {
      printf("%s * %s", class->instance_type, tok_str(tok));
    } else {
      printf("%s", tok_str(tok));
    }
  }
}

void
toks_print_i(ary_t * toks, size_t i) {
  for (; i < toks->len; i++) {
    tok_t * tok = tok_get(toks, i);
    if (tok->def == SELF) {
      printf("o_instance_type * ");
    }
    printf("%s", tok_str(tok));
  }
}

void
meth_del(class_t * class) {
  size_t len = class->meths.len;
  size_t i = 0;
  for (; i < len; i++) {
    meth_t * meth = meth_get(class, i);
    if (meth->or.name.string == NULL) {
      free(meth->nm.name.objs);
    } else {
      free(meth->or.ret.objs);
      free(meth->or.arg.objs);
    }
  }
  free(class->meths.objs);
}

#define STRLEN(str) lenof(str) - 1

void *
parse_header(utf_t * string, size_t size) {
  scan_t scan = scan_new(string, size);
  parse_term(&scan, CLASS);
  class_t * class = calloc(1, sizeof(class_t));
  class->class = parse_term(&scan, ID);
  tok_t tok = parse_next(&scan);
  if (parse_test(&tok, EXTENDS)) {
    parse_match(&scan, TERM);
    class->super = parse_term(&scan, ID);
    parse_term(&scan, LBLOCK);
  } else {
    tok_t * cls = &class->class;
    static utf_t basename[] = "Object";
    static tok_t base = {ID, STRLEN(basename), basename};
    if (cls->len != STRLEN(basename) ||
        memcmp(cls->string, basename, STRLEN(basename)) != 0) {
      class->super = base;
    }
    parse_check(&tok, LBLOCK);
    parse_match(&scan, TERM);
  }
  parse_term(&scan, STRUCT);
  parse_match(&scan, LBLOCK);
  size_t level = 1;
  scan.scan_tok = scan_ctoken;
  tok = parse_next(&scan);
  class->strukt = tok;
  class->strukt.len = 0;
  while (1) {
    if (parse_test(&tok, LBLOCK)) {
      level++;
    } else if (parse_test(&tok, RBLOCK)) {
      level--;
    }
    if (level == 0) break;
    class->strukt.len += tok.len;
    tok = parse_next(&scan);
  }
  scan.scan_tok = scan_token;
  parse_match(&scan, TERM);
  parse_term(&scan, METHODS);
  parse_match(&scan, LBLOCK);
  scan.scan_tok = scan_ctoken;
  meth_t meth = {0};
  meth_new(class, 4);
  while (1) {
    tok_t tok = parse_next(&scan);
    if (parse_test(&tok, RBLOCK)) {
      break;
    } else if (parse_test(&tok, METHOD)) {
      meth.or.name = tok;
    } else if (parse_test(&tok, STAT)) {
      meth_add(class, &meth);
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
  class->super_header = class_prefix(super, "", "-h.c", tok_underscore);
  class->class_type = class_prefix(klass, "", "_class_t", tok_underscore);
  class->super_type = class_prefix(super, "", "_class_t", tok_underscore);
  class->instance_type = class_prefix(klass, "", "_t", tok_underscore);
  class->class_name = class_prefix(klass, "", "_class", tok_underscore);
  class->instance_name = class_prefix(klass, "", "", tok_underscore);
  class->super_instance_name = class_prefix(super, "", "", tok_underscore);
  class->class_prefix = class_prefix(klass, "", "_class_", tok_underscore);
  class->super_prefix = class_prefix(super, "", "_class_", tok_underscore);
  class->methods_name = class_prefix(klass, "", "_class_methods",
                                     tok_underscore);
  class->instances_name = class_prefix(klass, "", "_instance_variables",
                                       tok_underscore);
  class->super_methods_name = class_prefix(super, "", "_class_methods",
                                           tok_underscore);
  class->super_instances_name = class_prefix(super, "", "_instance_variables",
                                             tok_underscore);
  class->init_name = class_prefix(klass, "", "_class_init", tok_underscore);
}

// Fowler–Noll–Vo hash function
typedef utf_t * h_data_t;
typedef uintptr_t h_size_t;

#define FNV1_32A_INIT 0x811c9dc5
#define FNV_32_PRIME 0x01000193

static h_size_t
h_hash(h_data_t string, h_size_t len) {
  register h_size_t hval = FNV1_32A_INIT;
  // FNV-1a
  h_size_t i = 0;
  for (; i < len; i++) {
    hval ^= * string++;
    hval *= FNV_32_PRIME;
  }
  return hval;
}

typedef struct h_entry {
  h_size_t hash;
  h_size_t klen; // key len
  h_data_t key;
  h_data_t val;
  struct h_entry * next;
  struct h_entry * fore, * back;
} h_entry;

typedef struct {
  h_size_t capa;
  h_size_t len;
  h_entry ** bins;
  h_entry * head, * tail;
} h_table;

h_size_t
h_bin_pos(h_table * table, h_size_t hval) {
  return hval % table->capa;
}

h_entry *
h_new_entry(h_table * table, h_data_t key, h_size_t klen,
            h_data_t val, h_size_t hval, h_size_t pos) {
  h_entry * entry = calloc(1, sizeof(h_entry));
  entry->hash = hval;
  entry->klen = klen;
  entry->key = key;
  entry->val = val;
  entry->next = table->bins[pos];
  table->bins[pos] = entry;
  return entry;
}

void
h_realloc(h_table * table, h_size_t capa) {
  table->bins = realloc(table->bins, capa * sizeof(h_entry *));
  memset(table->bins, 0, capa * sizeof(h_entry *));
  table->capa = capa;
}

#define H_DEFAULT_INIT_TABLE_SIZE 11
#define H_DEFAULT_SECOND_TABLE_SIZE 19
#define H_MINSIZE 8

// Table of prime numbers 2^n+a, 2<=n<=30.
static const uint_fast32_t h_primes[] = {
  H_DEFAULT_INIT_TABLE_SIZE,
  H_DEFAULT_SECOND_TABLE_SIZE,
  32 + 5,
  64 + 3,
  128 + 3,
  256 + 27,
  512 + 9,
  1024 + 9,
  2048 + 5,
  4096 + 3,
  8192 + 27,
  16384 + 43,
  32768 + 3,
  65536 + 45,
  131072 + 29,
  262144 + 3,
  524288 + 21,
  1048576 + 7,
  2097152 + 17,
  4194304 + 15,
  8388608 + 9,
  16777216 + 43,
  33554432 + 35,
  67108864 + 15,
  134217728 + 29,
  268435456 + 3,
  536870912 + 11,
  1073741824 + 85,
  0
};

h_size_t
h_new_capa(h_size_t old) {
  h_size_t new = H_MINSIZE;
  h_size_t i = 0;
  for (; i < lenof(h_primes); i++) {
    if (new > old) return h_primes[i];
    new <<= 1;
  }
  puts("hash table too big");
  exit(0);
  return -1;
}

void
h_rehash(h_table * table) {
  h_size_t capa = h_new_capa(table->capa + 1);
  h_realloc(table, capa);
  h_entry * entry = table->head;
  if (entry != 0) {
    do {
      h_size_t pos = h_bin_pos(table, entry->hash);
      entry->next = table->bins[pos];
      table->bins[pos] = entry;
      entry = entry->fore;
    } while (entry != 0);
  }
}

#define H_DEFAULT_MAX_DENSITY 5

void
h_add(h_table * table, h_data_t key, h_size_t klen,
      h_data_t val, h_size_t hval, h_size_t pos) {
  if (table->len > H_DEFAULT_MAX_DENSITY * table->capa) {
    h_rehash(table);
    pos = h_bin_pos(table, hval);
  }
  h_entry * entry = h_new_entry(table, key, klen, val, hval, pos);
  if (table->head != 0) {
    entry->fore = table->tail;
    table->tail->back = entry;
    entry->back = 0;
    table->tail = entry;
  } else {
    table->head = table->tail = entry;
    entry->fore = entry->back = 0;
  }
  table->len++;
}

int
h_eq(h_data_t a, h_size_t alen, h_data_t b, h_size_t blen) {
  return a == b || alen == blen && strncmp(a, b, alen);
}

int
h_hit(h_entry * entry, h_data_t key, h_size_t klen, h_size_t hval) {
  return entry != 0 && (entry->hash != hval ||
                        h_eq(entry->key, entry->klen, key, klen));
}

h_entry *
h_find(h_table * table, h_data_t key, h_size_t klen,
       h_size_t hval, h_size_t pos) {
  h_entry * entry = table->bins[pos];
  if (h_hit(entry, key, klen, hval)) {
    while (h_hit(entry->next, key, klen, hval)) {
      entry = entry->next;
    }
    entry = entry->next;
  }
  return entry;
}

typedef void h_lookup_t(h_table * table,
                        h_data_t key, h_size_t klen,
                        h_data_t * val, h_size_t hval, h_size_t pos,
                        h_entry * entry);

int
h_lookup(h_table * table, h_data_t key, h_size_t klen, h_data_t * val,
         h_lookup_t * yield) {
  h_size_t hval = h_hash(key, klen);
  h_size_t pos = h_bin_pos(table, hval);
  h_entry * entry = h_find(table, key, klen, hval, pos);
  yield(table, key, klen, val, hval, pos, entry);
  return entry != NULL;
}

void
h_insert_cb(h_table * table,
            h_data_t key, h_size_t klen,
            h_data_t * val, h_size_t hval, h_size_t pos, h_entry * entry) {
  if (entry == NULL) {
    h_add(table, key, klen, (h_data_t) val, hval, pos);
  } else {
    entry->val = (h_data_t) val;
  }
}

void
h_get_cb(h_table * table,
         h_data_t key, h_size_t klen,
         h_data_t * val, h_size_t hval, h_size_t pos, h_entry * entry) {
  if (entry != NULL && val != NULL) {
    * val = entry->val;
  }
}

int
h_insert(h_table * table, h_data_t key, h_size_t klen, h_data_t val) {
  return h_lookup(table, key, klen, (h_data_t *) val, h_insert_cb);
}

int
h_get(h_table * table, h_data_t key, h_size_t klen, h_data_t * val) {
  return h_lookup(table, key, klen, val, h_get_cb);
}

int
h_contains(h_table * table, h_data_t key, h_size_t klen) {
  return h_lookup(table, key, klen, 0, h_get_cb);
}

h_table *
h_init_with_capa(h_size_t capa) {
  capa = h_new_capa(capa);
  h_table * table = calloc(1, sizeof(h_table));
  table->capa = capa;
  table->bins = calloc(capa, sizeof(h_entry *));
  return table;
}

h_table *
h_init(void) {
  return h_init_with_capa(0);
}

void
h_clear(h_table * table) {
  h_size_t i = 0;
  for (; i < table->capa; i++) {
    h_entry * entry = table->bins[i];
    while (entry != 0) {
      h_entry * next = entry->next;
      free(entry);
      entry = next;
    }
    table->bins[i] = 0;
  }
  table->len = 0;
  table->head = 0;
  table->tail = 0;
}

void
h_free(h_table * table) {
  h_clear(table);
  free(table->bins);
  free(table);
}

void *
build_header(utf_t * string, size_t size) {
  class_t * class = parse_header(string, size);
  size_t i = 0;
  class_types(class);
  ary_t parents = {0};
  class_new(&parents);
  class_add(&parents, class);
  class_t * klass = class;
  while (klass->super.string != NULL) {
    klass = file_read(1, class->super_header, parse_header);
    class_add(&parents, klass);
  }
  h_table * meths = h_init();
  i = 0;
  for (; i < parents.len; i++) {
    size_t reverse = parents.len - i - 1;
    class_t * klass = class_get(&parents, reverse);
    size_t mi = 0;
    for (; mi < klass->meths.len; mi++) {
      meth_t * meth = meth_get(klass, mi);
      tok_t * name = &meth->or.name;
      h_insert(meths, name->string + 1, (h_size_t) (name->len - 1),
               (h_data_t) meth);
    }
  }
  printf("#ifndef %s\n", class->header);
  printf("#define %s\n", class->header);
  puts("");
  printf("#include \"%s.h\"\n", class->super_instance_name);
  puts("");
  printf("typedef struct %s %s;\n", class->class_name, class->class_type);
  printf("typedef struct %s %s;\n", class->instance_name, class->instance_type);
  puts("");
  printf("struct %s {", class->class_name);
  h_entry * entry = meths->head;
  while (entry) {
    meth_t * meth = (meth_t *) entry->val;
    tok_t * name = &meth->or.name;
    if (name->string != NULL) {
      printf("  ");
      toks_print(class, &meth->or.ret);
      printf("%s", tok_str(&meth->or.name) + 1);
      toks_print(class, &meth->or.arg);
      printf(";");
    }
    entry = entry->back;
  }
  h_free(meths);
  printf("\n};\n");
  puts("");
  printf("extern %s %s;\n", class->class_type, tok_str(&class->class));
  puts("");
  printf("#define %s() \\\n", class->instances_name);
  printf("  %s(); \\\n", class->super_instances_name);
  printf("%s\n", tok_str(&class->strukt) + 1);
  printf("struct %s {\n", class->instance_name);
  printf("  %s()\n", class->instances_name);
  printf("};\n");
  puts("");
  printf("void %s(void);\n", class->init_name);
  puts("");
  printf("#endif\n");
  free(class->header);
  free(class->class_type);
  meth_del(class);
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
