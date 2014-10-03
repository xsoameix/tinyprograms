#define P00_ARG(                                         \
         _1, _2, _3, _4, _5, _6, _7, _8,                 \
         _9, _10, _11, _12, _13, _14, _15, _16,          \
         _17, _18, _19, _20, _21, _22, _23, _24,         \
         _25, _26, _27, _28, _29, _30, _31, _32,         \
         _33, _34, _35, _36, _37, _38, _39, _40,         \
         _41, _42, _43, _44, _45, _46, _47, _48,         \
         _49, _50, _51, _52, _53, _54, _55, _56,         \
         _57, _58, _59, _60, _61, _62, _63, _64,         \
         _65, _66, _67, _68, _69, _70, _71, _72,         \
         _73, _74, _75, _76, _77, _78, _79, _80,         \
         _81, _82, _83, _84, _85, _86, _87, _88,         \
         _89, _90, _91, _92, _93, _94, _95, _96,         \
         _97, _98, _99, _100, _101, _102, _103, _104,    \
         _105, _106, _107, _108, _109, _110, _111, _112, \
         _113, _114, _115, _116, _117, _118, _119, _120, \
         _121, _122, _123, _124, _125, _126, _127, _128, \
         _129, _130, _131, _132, _133, _134, _135, _136, \
         _137, _138, _139, _140, _141, _142, _143, _144, \
         _145, _146, _147, _148, _149, _150, _151, _152, \
         _153, _154, _155, _156, _157, _158, _159,       \
 ...) _159
#define P99_HAS_COMMA(...) P00_ARG(__VA_ARGS__,  \
         1, 1, 1, 1, 1, 1, 1,    \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 1, 1, \
         1, 1, 1, 1, 1, 1, 0, 0)
#define P00_NARG(...) P00_NARG_1(__VA_ARGS__)
#define P00_NARG_1(...) P00_ARG(__VA_ARGS__,     \
         158, 157, 156, 155, 154, 153, 152,      \
         151, 150, 149, 148, 147, 146, 145, 144, \
         143, 142, 141, 140, 139, 138, 137, 136, \
         135, 134, 133, 132, 131, 130, 129, 128, \
         127, 126, 125, 124, 123, 122, 121, 120, \
         119, 118, 117, 116, 115, 114, 113, 112, \
         111, 110, 109, 108, 107, 106, 105, 104, \
         103, 102, 101, 100,  99,  98,  97,  96, \
          95,  94,  93,  92,  91,  90,  89,  88, \
          87,  86,  85,  84,  83,  82,  81,  80, \
          79,  78,  77,  76,  75,  74,  73,  72, \
          71,  70,  69,  68,  67,  66,  65,  64, \
          63,  62,  61,  60,  59,  58,  57,  56, \
          55,  54,  53,  52,  51,  50,  49,  48, \
          47,  46,  45,  44,  43,  42,  41,  40, \
          39,  38,  37,  36,  35,  34,  33,  32, \
          31,  30,  29,  28,  27,  26,  25,  24, \
          23,  22,  21,  20,  19,  18,  17,  16, \
          15,  14,  13,  12,  11,  10,   9,   8, \
           7,   6,   5,   4,   3,   2,   1,   0,)
//P99_HAS_COMMA() = 0
//P99_HAS_COMMA(A) = 0
//P99_HAS_COMMA(A, B) = 1
//P99_HAS_COMMA(A, B, C) = 1
//P99_HAS_COMMA(A, B, C, D) = 1
#define P99_IS_EQ_0(...) P99_TOK_EQ(0, __VA_ARGS__)
#define P99_TOK_EQ(TOK, ...)  P00_TOK_EQ_(P99_PASTE3(P00_IS_, TOK, _EQ_), __VA_ARGS__)
#define P00_TOK_EQ_(MAC, ...)  P00_TOK_EQ__(MAC, __VA_ARGS__)
#define P00_TOK_EQ__(MAC, ...) P99_HAS_COMMA(P99_PASTE2(P00_TOK_EQ_, P00_NARG(MAC ## __VA_ARGS__ (~) MAC ## __VA_ARGS__))(~))
//#define P00_TOK_EQ__(MAC, ...) P00_NARG(MAC ## __VA_ARGS__ (~) MAC ## __VA_ARGS__)
#define P00_TOK_EQ_0(...) ~
#define P00_TOK_EQ_1(...) ~
#define P00_TOK_EQ_2(...) ,
#define P00_TOK_EQ_3(...) ~
#define P00_TOK_EQ_4(...) ~
#define P99_ADD(_0, _1) \
    P00_ADD_(_0, _1, P99_IS_EQ_0(_0), \
                     P99_IS_EQ_0(_1), \
                     P99_NARG(P99_SELS(_0, P00_ALL_ZEROES()), \
                              P99_SELS(_1, P00_ALL_ZEROES())))
#define P00_ADD_(_0, _1, _2, _3, _4) P99_PASTE3(P00_ADD_, _2, _3)(_0, _1, _4)
#define P00_ADD_00(_0, _1, _2) _2
#define P00_ADD_01(_0, _1, _2) _0
#define P00_ADD_10(_0, _1, _2) _1
#define P00_ADD_11(_0, _1, _2) 0
#define P00_IS_0_EQ_0(...) ,
#define P99_CAT2(_1, _2) _1 ## _2
#define P99_PASTE2(_1, _2) P99_CAT2(_1, _2)
#define P99_PASTE3(_1,  _2, _3)                                \
      P99_PASTE2(P99_PASTE2(_1, _2), _3)
//#define A_(...) P99_IS_EQ_0(__VA_ARGS__)
//#define A(...) A_(__VA_ARGS__)
//P99_IS_EQ_0(0)
//P99_IS_EQ_0(1)
//P00_TOK_EQ__(P00_IS_0_EQ_, 0)
//P00_TOK_EQ__(P00_IS_0_EQ_, 1)
//P00_NARG()
//P00_NARG(100)
//P00_NARG(100, 100)

#define PUBLIC_METHODS_SIZE 4
#define PUBLIC_METHOD_0 foo
#define PUBLIC_METHOD_1 bar
#define PUBLIC_METHOD_2 far
#define PUBLIC_METHOD_3 car
#define PUBLIC_METHOD_4 lar
#define PRINT_METHODS ARY_UPTO(PUBLIC_METHODS_SIZE, PUBLIC_METHOD_)
#define PRINT_METHOD(n) STR_CAT(PUBLIC_METHOD_, n)
#define STR_CAT(a, b) a ## b
#define ARY_UPTO(n, e) STR_CAT(ARY_UPTO_, n)(n, e)
#define ARY_UPTO_0(n, e)
#define ARY_UPTO_1(n, e) STR_CAT(e, 0)
#define ARY_UPTO_2(n, e) ARY_UPTO_1(n, e) STR_CAT(e, 1)
#define ARY_UPTO_3(n, e) ARY_UPTO_2(n, e) STR_CAT(e, 2)
#define ARY_UPTO_4(n, e) ARY_UPTO_3(n, e) STR_CAT(e, 3)
#define ARY_UPTO_5(n, e) ARY_UPTO_4(n, e) STR_CAT(e, 4)
#define ARY_UPTO_6(n, e) ARY_UPTO_5(n, e) STR_CAT(e, 5)
#define ARY_UPTO_7(n, e) ARY_UPTO_6(n, e) STR_CAT(e, 6)
#define ARY_UPTO_8(n, e) ARY_UPTO_7(n, e) STR_CAT(e, 7)
#define ARY_UPTO_9(n, e) ARY_UPTO_8(n, e) STR_CAT(e, 8)
#define ARY_UPTO_10(n, e) ARY_UPTO_9(n, e) STR_CAT(e, 9)
#define ARY_UPTO_11(n, e) ARY_UPTO_10(n, e) STR_CAT(e, 10)
#define ARY_UPTO_12(n, e) ARY_UPTO_11(n, e) STR_CAT(e, 11)
#define ARY_UPTO_13(n, e) ARY_UPTO_12(n, e) STR_CAT(e, 12)
#define ARY_UPTO_14(n, e) ARY_UPTO_13(n, e) STR_CAT(e, 13)
#define ARY_UPTO_15(n, e) ARY_UPTO_14(n, e) STR_CAT(e, 14)
#define ARY_UPTO_16(n, e) ARY_UPTO_15(n, e) STR_CAT(e, 15)
#define ARY_UPTO_17(n, e) ARY_UPTO_16(n, e) STR_CAT(e, 16)
#define ARY_UPTO_18(n, e) ARY_UPTO_17(n, e) STR_CAT(e, 17)
#define ARY_UPTO_19(n, e) ARY_UPTO_18(n, e) STR_CAT(e, 18)
#define ARY_UPTO_20(n, e) ARY_UPTO_19(n, e) STR_CAT(e, 19)
#define ARY_UPTO_21(n, e) ARY_UPTO_20(n, e) STR_CAT(e, 20)
#define ARY_UPTO_22(n, e) ARY_UPTO_21(n, e) STR_CAT(e, 21)
#define ARY_UPTO_23(n, e) ARY_UPTO_22(n, e) STR_CAT(e, 22)
#define ARY_UPTO_24(n, e) ARY_UPTO_23(n, e) STR_CAT(e, 23)
#define ARY_UPTO_25(n, e) ARY_UPTO_24(n, e) STR_CAT(e, 24)
#define ARY_UPTO_26(n, e) ARY_UPTO_25(n, e) STR_CAT(e, 25)
#define ARY_UPTO_27(n, e) ARY_UPTO_26(n, e) STR_CAT(e, 26)
#define ARY_UPTO_28(n, e) ARY_UPTO_27(n, e) STR_CAT(e, 27)
#define ARY_UPTO_29(n, e) ARY_UPTO_28(n, e) STR_CAT(e, 28)
#define ARY_UPTO_30(n, e) ARY_UPTO_29(n, e) STR_CAT(e, 29)
#define ARY_UPTO_31(n, e) ARY_UPTO_30(n, e) STR_CAT(e, 30)
#define ARY_UPTO_32(n, e) ARY_UPTO_31(n, e) STR_CAT(e, 31)
#define ARY_UPTO_33(n, e) ARY_UPTO_32(n, e) STR_CAT(e, 32)
#define ARY_UPTO_34(n, e) ARY_UPTO_33(n, e) STR_CAT(e, 33)
#define ARY_UPTO_35(n, e) ARY_UPTO_34(n, e) STR_CAT(e, 34)
#define ARY_UPTO_36(n, e) ARY_UPTO_35(n, e) STR_CAT(e, 35)
#define ARY_UPTO_37(n, e) ARY_UPTO_36(n, e) STR_CAT(e, 36)
#define ARY_UPTO_38(n, e) ARY_UPTO_37(n, e) STR_CAT(e, 37)
#define ARY_UPTO_39(n, e) ARY_UPTO_38(n, e) STR_CAT(e, 38)
#define ARY_UPTO_40(n, e) ARY_UPTO_39(n, e) STR_CAT(e, 39)
#define ARY_UPTO_41(n, e) ARY_UPTO_40(n, e) STR_CAT(e, 40)
#define ARY_UPTO_42(n, e) ARY_UPTO_41(n, e) STR_CAT(e, 41)
#define ARY_UPTO_43(n, e) ARY_UPTO_42(n, e) STR_CAT(e, 42)
#define ARY_UPTO_44(n, e) ARY_UPTO_43(n, e) STR_CAT(e, 43)
#define ARY_UPTO_45(n, e) ARY_UPTO_44(n, e) STR_CAT(e, 44)
#define ARY_UPTO_46(n, e) ARY_UPTO_45(n, e) STR_CAT(e, 45)
#define ARY_UPTO_47(n, e) ARY_UPTO_46(n, e) STR_CAT(e, 46)
#define ARY_UPTO_48(n, e) ARY_UPTO_47(n, e) STR_CAT(e, 47)
#define ARY_UPTO_49(n, e) ARY_UPTO_48(n, e) STR_CAT(e, 48)
#define ARY_UPTO_50(n, e) ARY_UPTO_49(n, e) STR_CAT(e, 49)
STR_CAT(A, B)
# 1 "-"
ARY_UPTO(0, A_)
ARY_UPTO(1, A_)
ARY_UPTO(2, A_)
ARY_UPTO(3, A_)
# 1 "-"
PRINT_METHOD(0)
PRINT_METHOD(1)
PRINT_METHOD(2)
PRINT_METHOD(3)
# 1 "-"
PRINT_METHODS
