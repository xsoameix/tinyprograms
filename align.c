#include <stdio.h>
#include <stddef.h>
#include <stdalign.h>

#define align_of(type) \
  offsetof(struct { char c; type t; }, t)
#define print_size_and_align(type) \
  printf("%6s %4zu %6ld\n", #type, sizeof(type), align_of(type))

typedef struct {
  char a;
  int b;
  double c;
} foo_t;

typedef struct {
  char a;
  int b;
  long c;
} bar_t;

typedef struct {
  char a;
  int b;
  int c;
} ano_t;

int
main(void) {
  printf("[type][size][align]\n");
  print_size_and_align(char);
  print_size_and_align(int);
  print_size_and_align(long);
  print_size_and_align(double);
  print_size_and_align(foo_t);
  printf("%zu offset of char\n", offsetof(foo_t, a));
  printf("%zu offset of int\n", offsetof(foo_t, b));
  printf("%zu offset of double\n", offsetof(foo_t, c));
  print_size_and_align(bar_t);
  printf("%zu offset of char\n", offsetof(bar_t, a));
  printf("%zu offset of int\n", offsetof(bar_t, b));
  printf("%zu offset of long\n", offsetof(bar_t, c));
  print_size_and_align(ano_t);
  printf("%zu offset of char\n", offsetof(ano_t, a));
  printf("%zu offset of int\n", offsetof(ano_t, b));
  printf("%zu offset of int\n", offsetof(ano_t, c));
  alignas(8) int a;
  alignas(4) int b;
  char c;
  char d;
  printf("%6s %4zu %6ld %p\n", "a", sizeof(a), alignof(a), &a);
  printf("%6s %4zu %6ld %p\n", "b", sizeof(b), alignof(b), &b);
  printf("%6s %4zu %6ld %p\n", "c", sizeof(c), alignof(c), &c);
  printf("%6s %4zu %6ld %p\n", "d", sizeof(d), alignof(d), &d);
  return 0;
}
