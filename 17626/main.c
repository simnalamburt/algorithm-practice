#include <stdio.h>
#include <math.h>

int solve(int n) {
  int upper_bound = (int)sqrt(n) + 1;
  for (int b = 0; b < upper_bound; ++b) {
    for (int c = b; c < upper_bound; ++c) {
      for (int d = c; d < upper_bound; ++d) {
        if (b*b + c*c + d*d != n) { continue; }
        if (c == 0) { return 1; }
        if (b == 0) { return 2; }
        return 3;
      }
    }
  }
  return 4;
}

int main() {
  int n;
  scanf("%d", &n);
  printf("%d\n", solve(n));
}
