#pragma GCC optimize("O3")
#pragma GCC target("arch=haswell")
#include <stdio.h>

int main() {
  int N;
  scanf("%d", &N);
  int count[10001] = {0};
  for (int i = 0; i < N; ++i) {
    int n;
    scanf("%d", &n);
    ++count[n];
  }
  for (int i = 0; i < 10001; ++i) {
    int repeat = count[i];
    for (int j = 0; j < repeat; ++j) {
      printf("%d\n", i);
    }
  }
}
