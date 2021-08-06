#include <stdio.h>

int B, HEIGHTS[257];

int cost(int desired_height) {
  if (desired_height > 256) { goto FAILED; }

  int time_cost = 0;
  long block_cost = 0;
  for (int i = 0; i < 257; ++i) {
    int count = HEIGHTS[i];
    int diff = i - desired_height;
    time_cost += (diff > 0 ? 2 : -1) * diff * count;
    block_cost -= diff * count;
  }
  if (block_cost > B) { goto FAILED; }
  return time_cost;

FAILED:
  // Use ordered upper bound to make bisect work properly
  return 2100000000 + desired_height;
}

int main() {
  int N, M;
  scanf("%d%d%d", &N, &M, &B);
  for (int row = 0; row < N; ++row) {
    for (int col = 0; col < M; ++col) {
      int height;
      scanf("%d", &height);
      ++HEIGHTS[height];
    }
  }

  //
  // Find min using bisect
  //
  int lo = 0;
  int hi = 257;
  // Loop invariant:
  //   lo < hi
  //   lo is part of strictly monotonic decreasing sequence + global minimums
  //   hi is part of global minimums + strictly monotonic increasing sequence
  while (lo + 1 < hi) {
    int mid = (lo + hi)/2;
    if (cost(mid - 1) >= cost(mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  printf("%d %d\n", cost(lo), lo);
}
