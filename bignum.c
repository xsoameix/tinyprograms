#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef size_t bdigit;

typedef struct bignum {
  size_t len;
  bdigit * digits;
} bnum;

//bnum
//pow(bnum * base, int power) {
//  if (power == 0) return 1;
//  if (power == 1) return 1;
//}

const int bdigit_size = sizeof(bdigit);
const int bdigit_bits = sizeof(bdigit) * 8; // 8 bits per byte

// base 10
const size_t   maxpow16_exp = 4;
const uint16_t maxpow16_num = 0x00002710;
const size_t   maxpow32_exp = 9;
const uint32_t maxpow32_num = 0x3b9aca00;
const size_t   maxpow64_exp = 19;
const uint64_t maxpow64_num = 0x8ac72304 << 32 | 0x89e80000;

// base 10
bdigit
maxpow_in_bdigit(size_t * exp_ret) {
  bdigit maxpow;
  size_t exponent;
  if (bdigit_size == 2) {
    maxpow = maxpow16_num;
    exponent = maxpow16_exp;
  } else if (bdigit_size == 4) {
    maxpow = maxpow32_num;
    exponent = maxpow32_exp;
  } else if (bdigit_size == 8) {
    maxpow = maxpow64_num;
    exponent = maxpow64_exp;
  }
  * exp_ret = exponent;
  return maxpow;
}

bnum *
bignum_new(size_t bdigit_len) {
  bnum * bn = calloc(1, sizeof(bnum) + bdigit_len * bdigit_size);
  bn->len = bdigit_len;
  bn->digits = (void *) bn + sizeof(bnum);
  return bn;
}

bnum *
bignum_new_from_bit(int bits_len) {
  if (bits_len == 0) bits_len = 1;
  int bdigit_len = 1 + (bits_len - 1) / bdigit_bits;
  return bignum_new(bdigit_len);
}

bdigit
bit(size_t len) {
  return (bdigit) 1 << len;
}

void
set_bit(bdigit * num, size_t len) {
  * num |= bit(len);
}

void
bignum_set_bit(bnum * bn, size_t len) {
  int bdigit_i = len / bdigit_bits;
  int bit_i = len % bdigit_bits;
  set_bit(&bn->digits[bdigit_i], bit_i);
}

size_t
max(size_t a, size_t b) {
  return a > b ? a : b;
}

void
bignum_mul_karatsuba(bdigit * zds, size_t zn,
                     const bdigit * xds, size_t xn,
                     const bdigit * yds, size_t yn,
                     bdigit * wds, size_t wn,
                     size_t n) {
  /* Karatsuba algorithm:
   *
   * x = x1*r + x0
   * y = y1*r + y0
   * z = x*y
   *   = (x1*r + x0) * (y1*r + y0)
   *   = x1*y1*r^2 + (x1*y0 + x0*y1) * r + x0*y0
   *   = x1*y1*r^2 + (x1*y1 + x0*y0 - (x1 - x0)*(y1 - y0))*r + x0*y0
   *   = z2*r^2 + (z2 + z0 - z1)*r + z0
   *   = (z2 + hi(z2 + z0 - z1))*r^2 + (lo(z2 + z0 - z1) + hi(z0))*r + lo(z0)
   *
   * Example:
   *
   *        F F
   *        F F
   *   --------
   *        E 1
   *      E 1
   *      E 1
   *    E 1
   *    F E 0 1
   *
   * Parameters of this function:
   *
   *    w: total work area
   *    rw: work area for this function(caller)
   *    ew: work area for callee
   *
   * Procedure:
   *
   *    zds3:|x1-x0| zds2:? zds1:|y1-y0| zds0:? wds:?
   * => zds3:|x1-x0| zds2:? zds1:|y1-y0| zds0:? wds:|x1-x0|*|y1-y0|
   * => zds3,zds2:x1*y1 zds1,zds0:x0*y0 wds:x1*y1+x0*y0-|x1-x0|*|y1-y0|
   * => zds3:hi(x1*y1)
   *    zds2:lo(x1*y1)+hi(x1*y1+x0*y0-|x1-x0|*|y1-y0|)
   *    zds1:hi(x0*y0)+lo(x1*y1+x0*y0-|x1-x0|*|y1-y0|)
   *    zds0:lo(x0*y0)
   */
  const bdigit * x1 = xds + n;
  const bdigit * x0 = xds;
  const bdigit * y1 = yds + n;
  const bdigit * y0 = yds;
  bdigit * z3 = zds + n * 3;
  bdigit * z2 = zds + n * 2;
  bdigit * z1 = zds + n;
  bdigit * z0 = zds;
  bdigit * rw = wds;
  bdigit * ew = wds + n * 2;
  size_t x1n = xn - n;
  size_t x0n = n;
  size_t y1n = yn - n;
  size_t y0n = n;
  size_t rwn = n * 2;
  size_t ewn = wn - n * 2;
  assert(xn + yn <= zn);
  assert(xn <= yn);
  assert(yn < xn * 2);
  bool sub_it = 1;
  int is_signed1 = bignum_sub(z3, n, x1, x1n, x0, x0n);
  if (is_signed1) {
    bignum_2comp(z3, n);
    sub_p = !sub_p;
  }
  int is_signed2 = bignum_sub(z1, n, y1, y1n, y0, y0n);
  if (is_signed2) {
    bignum_2comp(z1, n);
    sub_p = !sub_p;
  }
  bignum_mul_karatsuba(rw, rwn, z3, n, z1, n, ew, ewn);
  bignum_mul_karatsuba(z2, n * 2, x1, x1n, y1, y1n, ew, ewn);
  bignum_mul_karatsuba(z0, n * 2, x0, x0n, y0, y0n, ew, ewn);
  if (sub_it) {
    bignum_2comp(rw, rwn);
  }
  bignum_add(rw, rwn, rw, rwn, z2, n * 2);
  bignum_add(rw, rwn, rw, rwn, z0, n * 2);
  bignum_add(z1, n * 3, rw, rwn, z1, n * 3);
}

void
bignum_mul_karatsuba_start(bdigit * zds, size_t zn,
                           const bdigit * xds, size_t xn,
                           const bdigit * yds, size_t yn) {
  size_t n = max(xn, yn) / 2;
  /* w = work area
   *   = 2 n space for karatsuba function usage +
   *       n space for karatsuba callee function usage (recursive)
   */
  size_t wn = n * 3;
  bdigits * wds = calloc(wn, bdigit_size);
  bignum_mul_karatsuba(zds, zn, xds, xn, yds, yn, wds, wn, n);
  free(wds);
}

void
bignum_mul(bdigit * zds, size_t zn,
           const bdigit * xds, size_t xn,
           const bdigit * yds, size_t yn) {
  return bignum_mul_karatsuba_start(zds, zn, xds, xn, yds, yn);
}

bnum *
bignum_sq(bnum * x) {
  bnum * z = bignew(x->len * 2);
  bignum_mul(z->digits, z->len,
             x->digits, x->len,
             x->digits, x->len);
}

void
bignum_realloc(bnum * x, size_t len) {
  realloc(x->digits, len * bdigit_size);
}

void
bignum_set_len(bnum * x, size_t len) {
  x->len = len;
}

void
bignum_resize(bnum * x, size_t len) {
  bignum_realloc(x, len);
  bignum_set_len(x, len);
}

bnum *
bignum_trunc(bnum * x) {
  if (x->len == 0) return x;
  size_t i = 0;
  size_t size;
  for (; i < x->len; i++) {
    size_t reverse_i = x->len - i - 1;
    if (!x->ds[reverse_i]) {
      size = reverse_i + 1;
      break;
    }
  }
  if (size < x->len) {
    bignum_resize(x, size);
  }
  return x;
}

bnum *      power_cache[bdigit_bits + 1] = {0};
size_t digits_len_cache[bdigit_bits + 1] = {0};

bnum *
get_power(int power_level, size_t * digits_len_ret) {
  if (power_cache[power_level] == NULL) {
    bnum * power;
    size_t digits_len;
    if (power_level == 0) {
      bdigit digit = maxpow_in_bdigit(&digits_len);
      power = bignum_new(2);
      power->digits[0] = digit;
    } else {
      power = get_power(power_level - 1, &digits_len);
      power = bignum_trunc(bignum_sq(power));
      digits_len *= 2;
    }
    power_cache[power_level] = power;
    digits_len_cache[power_level] = digits_len;
  }
  if (digits_len_ret) {
    * digits_len_ret = digits_len_cache[power_level];
  }
  return power_cache[power_level];
}

char *
bignum_to_s(bnum * x) {
  int power_level = 0;
  bnum * power = get_power(power_level, NULL);
  while (power < bdigit_bits &&
         power->len <= (x->len + 1) / 2) {
  }
}

int
main(void) {
  size_t m_len, n_len;
  while(scanf("%d %d", &m_len, &n_len) == 2) {
    bnum * m = bignum_new_from_bit(m_len);
    bignum_set_bit(m, m_len);
    printf("m_len %2d len %d digits %16zx %16zx\n",
        m_len, m->len, m->digits[0], m->digits[1]);
    //char * m = pow(2, m_len);
    //char * n = pow(2, n_len);
    //char * sum = add(m, n);
    //print_num(sum);
    free(m);
    //free(n);
    //free(sum);
  }
  return 0;
}
