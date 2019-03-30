// gcc solution.c -O2 -Wall -Wextra -Wpedantic -Werror
//
// Reference: https://www.acmicpc.net/problem/2749
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

typedef uint8_t u8;
typedef int64_t i64;

// Reference: https://en.wikipedia.org/wiki/Pisano_period
static const i64 MOD = 1000000;
static const i64 PISANO_PERIOD = 1500000;

static const u8 BASE_CASES[14] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233 };

static i64 fibo(const i64 n) {
  // Base cases
  if (n < 14) {
    return BASE_CASES[n];
  }

  // d'Ocagne's identity
  // Reference: https://en.wikipedia.org/wiki/Fibonacci_number#d'Ocagne's_identity
  const i64 k = n / 2;
  const i64 fibo_k0 = fibo(k);
  const i64 fibo_k1 = fibo(k + 1);
  const i64 answer = (
    n % 2 == 0 ?
    fibo_k0*(2*fibo_k1 - fibo_k0) :
    fibo_k1*fibo_k1 + fibo_k0*fibo_k0
  ) % MOD;
  return answer > 0 ? answer : answer + MOD;
}

int main() {
  i64 n;
  scanf("%" SCNd64, &n);

  const i64 answer = fibo(n % PISANO_PERIOD);
  printf("%" PRId64 "\n", answer);
}
