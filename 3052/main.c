#include <stdio.h>
#include <stdint.h>

int main() {
  uint64_t bitset = 0;
  for (int i = 0; i < 10; ++i) {
    int n;
    scanf("%d", &n);
    bitset |= 1lu << (n%42);
  }
  printf("%d\n", __builtin_popcountll(bitset));
}
