// gcc naive.c -O2 -Wall -Wextra -Wpedantic -Werror -lm -static -std=c11
#pragma GCC optimize("O3")
#pragma GCC target("arch=haswell")

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef __uint128_t u128;

// BigInt는 10**37 진법을 사용한다. 10**37 의 값이 BIGINT_RADIX에 저장되어있다.
//
//     37 = floor(log(2**128, 10)) - 1
//
// u128로 표현할 수 있는 제일 큰 10의 거듭제곱이 10**38 이기때문에 10**37 진법을
// 쓰도록 결정했다. 덧셈할때에 carry 처리를 편하게 하기 위해 10**38 진법 대신
// 10**37 진법을 쓰기로 하였다.
#define BIGINT_RADIX ((u128)1000000000000 * (u128)1000000000000 * (u128)10000000000000)

// BigInt의 자리수 한계
//
//     ceil(log(피보나치10000번째항, 10) / 37)
//
// 이 프로그램이 출력하는 제일 큰 값은 피보나치 수열의 10000번째 항인데, 이
// 숫자는 10**37 진법으로 표현할 경우 57개의 자리수로 표현할 수 있다. 그래서
// BigInt를 길이 57의 배열로 표현하였다.
#define BIGINT_LEN 57

typedef struct { u128 data[BIGINT_LEN]; } BigInt;

// lhs와 rhs를 더한 결과를 self에 저장함
static void bigint_add(BigInt *self, const BigInt *lhs, const BigInt *rhs) {
  u128 carry = 0;
  for (u8 i = 0; i < BIGINT_LEN; ++i) {
    const u128 num = lhs->data[i] + rhs->data[i] + carry;
    self->data[i] = num % BIGINT_RADIX;
    carry = num / BIGINT_RADIX;
  }
}

// param에 들어있는 값들을 복사하여 self에 저장함
static void bigint_set(BigInt *self, const BigInt* param) {
  for (u8 i = 0; i < BIGINT_LEN; ++i) {
    self->data[i] = param->data[i];
  }
}

// self가 0인지 아닌지 여부를 출력함
//
// Examples:
//   bigint_find_msd(0) => true
//   bigint_find_msd(1234) => false
static bool bigint_is_zero(const BigInt *self) {
  for (u8 i = 0; i < BIGINT_LEN; ++i) {
    if (self->data[i]) {
      return false;
    }
  }
  return true;
}

// self의 MSD가 몇번째 인덱스인지 출력함. self가 0일경우 -1 반환함
//
// Examples:
//   bigint_find_msd(0) => -1
//   bigint_find_msd(1234) => 0
//   bigint_find_msd(10**40) => 1
//   bigint_find_msd(10**90) => 2
static i8 bigint_find_msd(const BigInt *self) {
  for (i8 digit = BIGINT_LEN-1; digit >= 0; --digit) {
    if (self->data[digit]) {
      return digit;
    }
  }
  return -1;
}

// file에 self를 출력함
static void bigint_fprint(const BigInt *self, FILE* file) {
  if (bigint_is_zero(self)) {
    puts("0");
    return;
  }

  const i8 msd_digit = bigint_find_msd(self);

  // 10**37진법에서 제일 큰 자리수부터 하나씩 출력함
  char buffer[37];
  for (i8 digit = msd_digit; digit >= 0; --digit) {
    u128 num = self->data[digit];

    // 10**37 진법의 자리수 하나 num 을 buffer에 10진수로 변환
    i8 j = 36;

    for (; j >= 0; --j) {
      // MSD를 출력하고있는 경우에만 leading zero를 스킵해야함
      if (num == 0 && digit == msd_digit) {
        break;
      }

      buffer[j] = "0123456789"[num % 10];
      num /= 10;
    }
    ++j;
    // 현재 buffer에 10진수 숫자가 '37 - j'개 만큼 기록되었음

    // buffer 출력
    fwrite(&buffer[j], 1, 37 - j, file);
  }
}

int main() {
  u16 num;
  scanf("%"SCNu16, &num);

  BigInt a = { .data = {0} };
  BigInt b = { .data = {1} };
  while (num > 0) {
    BigInt tmp;
    bigint_add(&tmp, &a, &b);
    bigint_set(&a, &b);
    bigint_set(&b, &tmp);
    --num;
  }
  bigint_fprint(&a, stdout);
  fputc('\n', stdout);
}
