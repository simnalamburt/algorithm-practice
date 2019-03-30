// Reference: https://en.wikipedia.org/wiki/Pisano_period

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

typedef uint32_t u32;
typedef uint64_t u64;

static const u32 mod = 1000000;
static const u32 pisano_period = 1500000;

int main() {
  u64 n;
  scanf("%" SCNu64, &n);

  n %= pisano_period;

  u32 a = 0;
  u32 b = 1;
  while (n-- > 0) {
    const u32 c = (a + b)%mod;
    a = b;
    b = c;
  }

  printf("%" PRIu32 "\n", a);
}
