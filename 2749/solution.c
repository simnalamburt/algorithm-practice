// gcc solution.c -O2 -Wall -Wextra -Wpedantic -Werror
//
// Reference: https://www.acmicpc.net/problem/2749
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

typedef uint8_t u8;
typedef int64_t i64;

// Pisano period
// Reference: https://en.wikipedia.org/wiki/Pisano_period
static const i64 MOD = 1000000;
static const i64 PISANO_PERIOD = 1500000;

static const u8 BASE_CASES[14] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233 };

static i64 fibo(const i64 num) {
  // Base cases
  if (num < 14) {
    return BASE_CASES[num];
  }

  // d'Ocagne's identity
  // Reference: https://en.wikipedia.org/wiki/Fibonacci_number#d'Ocagne's_identity
  const i64 k = num / 2;
  const i64 fibo_k0 = fibo(k);
  const i64 fibo_k1 = fibo(k + 1);
  const i64 answer = (
    num % 2 == 0 ?
    fibo_k0*(2*fibo_k1 - fibo_k0) :
    fibo_k1*fibo_k1 + fibo_k0*fibo_k0
  ) % MOD;
  return answer >= 0 ? answer : answer + MOD;
}

int main() {
  i64 num;
  scanf("%" SCNd64, &num);

  const i64 answer = fibo(num % PISANO_PERIOD);
  printf("%" PRId64 "\n", answer);
}
