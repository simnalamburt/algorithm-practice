// on Linux:
//   gcc naive.c -O2 -Wall -Wextra -Wpedantic -Werror -lm -static -std=c11
//
// on macOS:
//   clang naive.c -O2 -Wall -Wextra -Wpedantic -Werror -lm -std=c11

// Use only with gcc
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC optimize("O3")
#pragma GCC target("arch=haswell")
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef uint64_t u64;

// BigInt는 10**18 진법을 사용한다. 10**18 의 값이 BIGINT_RADIX에 저장되어있다.
//
//     18 = floor(log(2**64, 10)) - 1
//
// u64로 표현할 수 있는 제일 큰 10의 거듭제곱이 10**38 이기때문에 10**18 진법을
// 쓰도록 결정했다. 덧셈할때에 carry 처리를 편하게 하기 위해 10**38 진법 대신
// 10**18 진법을 쓰기로 하였다.
#define BIGINT_RADIX 1000000000000000000
#define BIGINT_RADIX_LOG10 18

// BigInt의 자리수 한계
//
//     ceil(log(피보나치10000번째항, 10) / 18)
//
// 이 프로그램이 출력하는 제일 큰 값은 피보나치 수열의 10000번째 항인데, 이
// 숫자는 10**18 진법으로 표현할 경우 117개의 자리수로 표현할 수 있다. 그래서
// BigInt를 길이 117의 배열로 표현하였다.
#define BIGINT_MAX_LEN 117

typedef struct {
  u8 len;
  u64 data[BIGINT_MAX_LEN];
} BigInt;

// lhs와 rhs를 더한 결과를 self에 저장함
static void bigint_add(BigInt *self, const BigInt *lhs, const BigInt *rhs) {
  if (lhs->len < rhs->len) {
    const BigInt *tmp;
    // swap
    tmp = lhs;
    lhs = rhs;
    rhs = tmp;
  }

  // assert(lhs->len >= rhs->len)
  self->len = lhs->len;

  u64 carry = 0;
  for (u8 i = 0; i < rhs->len; ++i) {
    const u64 num = lhs->data[i] + rhs->data[i] + carry;
    self->data[i] = num % BIGINT_RADIX;
    carry = num / BIGINT_RADIX;
  }
  for (u8 i = rhs->len; i < lhs->len; ++i) {
    const u64 num = lhs->data[i] + carry;
    self->data[i] = num % BIGINT_RADIX;
    carry = num / BIGINT_RADIX;
  }

  if (carry) {
    self->data[self->len++] = carry;
  }
  // TODO: BIGINT_MAX_LEN 넘어가면 안됨
}

// param에 들어있는 값들을 복사하여 self에 저장함
static void bigint_set(BigInt *self, const BigInt* param) {
  self->len = param->len;
  for (u8 i = 0; i < param->len; ++i) {
    self->data[i] = param->data[i];
  }
}

static void bigint_set_u64(BigInt *self, u64 param) {
  if (param) {
    // non-zero
    self->len = 1;
    self->data[0] = param;
  } else {
    // zero
    self->len = 0;
  }
}

// self가 0인지 아닌지 여부를 출력함
//
// Examples:
//   bigint_find_msd(0) => true
//   bigint_find_msd(1234) => false
static bool bigint_is_zero(const BigInt *self) {
  return self->len == 0;
}

// file에 self를 출력함
static void bigint_print(const BigInt *self, FILE* file) {
  if (bigint_is_zero(self)) {
    puts("0");
    return;
  }

  const i8 msd_digit = ((i8)self->len) - 1;

  // 10**18진법에서 제일 큰 자리수부터 하나씩 출력함
  char buffer[BIGINT_RADIX_LOG10];
  for (i8 digit = msd_digit; digit >= 0; --digit) {
    u64 num = self->data[digit];

    // 10**18 진법의 자리수 하나 num 을 buffer에 10진수로 변환
    i8 j = BIGINT_RADIX_LOG10 - 1;

    for (; j >= 0; --j) {
      // MSD를 출력하고있는 경우에만 leading zero를 스킵해야함
      if (num == 0 && digit == msd_digit) {
        break;
      }

      buffer[j] = "0123456789"[num % 10];
      num /= 10;
    }
    ++j;
    // 현재 buffer에 10진수 숫자가 '18 - j'개 만큼 기록되었음

    // buffer 출력
    fwrite(&buffer[j], 1, BIGINT_RADIX_LOG10 - j, file);
  }
}

int main() {
  u16 num;
  scanf("%"SCNu16, &num);

  BigInt a, b;
  bigint_set_u64(&a, 0);
  bigint_set_u64(&b, 1);
  while (num > 0) {
    BigInt tmp;
    bigint_add(&tmp, &a, &b);
    bigint_set(&a, &b);
    bigint_set(&b, &tmp);
    --num;
  }
  bigint_print(&a, stdout);
  fputc('\n', stdout);
}
