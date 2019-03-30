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
static const i64 MODULO = 1000000;
static const i64 PISANO_PERIOD = 1500000;

static const u8 BASE_CASES[14] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233 };

typedef struct { i64 _0, _1; } Pair;

// fibo2(num) 은 num번째와 num+1 번째 피보나치 수를 반환하는 함수다
static Pair fibo2(const i64 num) {
  // Base cases
  if (num < 13) {
    return (Pair) { ._0 = BASE_CASES[num], ._1 = BASE_CASES[num+1] };
  }

  // d'Ocagne's identity
  // Reference: https://en.wikipedia.org/wiki/Fibonacci_number#d'Ocagne's_identity
  const i64 k = num / 2;
  const Pair fibo_k = fibo2(k);
  Pair answer = (
    num % 2 == 0 ?
    (Pair) { ._0 = fibo_k._0*(2*fibo_k._1 - fibo_k._0), ._1 = fibo_k._0*fibo_k._0 + fibo_k._1*fibo_k._1 } :
    (Pair) { ._0 = fibo_k._0*fibo_k._0 + fibo_k._1*fibo_k._1, ._1 = fibo_k._1*(2*fibo_k._0 + fibo_k._1) }
  );

  // Mod out
  answer._0 %= MODULO;
  answer._1 %= MODULO;
  if (answer._0 < 0) { answer._0 += MODULO; }
  if (answer._1 < 0) { answer._1 += MODULO; }
  return answer;
}

int main() {
  i64 num;
  scanf("%" SCNd64, &num);

  const i64 answer = fibo2(num % PISANO_PERIOD)._0;
  printf("%" PRId64 "\n", answer);
}
