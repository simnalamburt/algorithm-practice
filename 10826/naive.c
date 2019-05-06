// gcc naive.c -O2 -Wall -Wextra -Wpedantic -Werror -lm -static -std=c11
#pragma GCC optimize("O3")
#pragma GCC target("arch=haswell")

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

typedef int64_t i64;
typedef uint64_t u64;
typedef __uint128_t u128;
#define BIGINT_LEN 109
typedef struct { u64 data[BIGINT_LEN]; } BigInt;

void bigint_add(BigInt *self, const BigInt *lhs, const BigInt *rhs) {
  u64 carry = 0;
  for (u64 i = 0; i < BIGINT_LEN; ++i) {
    const u64 overflow1 = __builtin_add_overflow(lhs->data[i], rhs->data[i], &self->data[i]);
    const u64 overflow2 = __builtin_add_overflow(self->data[i], carry, &self->data[i]);
    carry = overflow1 + overflow2;
  }
}

void bigint_set(BigInt *self, const BigInt* param) {
  for (u64 i = 0; i < BIGINT_LEN; ++i) {
    self->data[i] = param->data[i];
  }
}

bool bigint_eq(const BigInt *self, const BigInt *param) {
  for (u64 i = 0; i < BIGINT_LEN; ++i) {
    if (self->data[i] != param->data[i]) {
      return false;
    }
  }
  return true;
}

void bigint_divmod(const BigInt *self, u64 divider, BigInt *p_quot, u64 *p_rem) {
  u128 rem = 0;
  const u128 divid = (u128)divider;
  for (i64 i = BIGINT_LEN-1; i >= 0; --i) {
    const u128 num = rem*(((u128)1) << ((u128)64)) + ((u128)self->data[i]);
    p_quot->data[i] = num / divid;
    rem = num % divid;
  }
  *p_rem = (u64)rem;
}

void bigint_println(const BigInt *self) {
  const BigInt zero = { .data = {0} };
  if (bigint_eq(self, &zero)) {
    puts("0");
    return;
  }

  BigInt tmp;
  bigint_set(&tmp, self);

  char buffer[2101];
  buffer[2100] = '\0';
  u64 digit = 0;
  do {
    u64 rem;
    bigint_divmod(&tmp, 10, &tmp, &rem);
    buffer[2100 - digit] = "0123456789"[rem];
    ++digit;
  } while (!bigint_eq(&tmp, &zero));
  puts(&buffer[2100 - digit + 1]);
}

int main() {
  u64 num;
  scanf("%"SCNu64, &num);

  BigInt a = { .data = {0} };
  BigInt b = { .data = {1} };
  while (num > 0) {
    BigInt tmp;
    bigint_add(&tmp, &a, &b);
    bigint_set(&a, &b);
    bigint_set(&b, &tmp);
    --num;
  }
  bigint_println(&a);
}
