#include <stdio.h>

int B, HEIGHTS[257];

int cost(int target) {
  int get = 0, used = 0;
  for (int i = 0; i < target; ++i) { used += (target - i) * HEIGHTS[i]; }
  for (int i = target + 1; i < 257; ++i) { get += (i - target) * HEIGHTS[i]; }

  int block_cost = used - get;
  int time_cost = used + 2*get;

  if (block_cost > B) {
    // Use ordered upper bound to make bisect work properly
    return 2100000000 + target;
  }
  return time_cost;
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
  // Find lower bound and upper bound
  //
  int lo = 0, hi = 257;
  for (int i = 0; i < 257; ++i) { if (HEIGHTS[i]) { lo = i; break; } }
  for (int i = 256; i >= 0; --i) { if (HEIGHTS[i]) { hi = i + 1; break; } }

  // Perform binary search
  //
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