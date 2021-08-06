#include <stdio.h>

int B, HEIGHTS[257];
int CACHE[257] = {
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1
};

int cost(int target) {
  if (CACHE[target] != -1) { return CACHE[target]; }

  int get = 0, used = 0;
  for (int i = 0; i < target; ++i) { used += (target - i) * HEIGHTS[i]; }
  for (int i = target + 1; i < 257; ++i) { get += (i - target) * HEIGHTS[i]; }
  int ret = used <= B + get ?
    used + 2*get :
    2100000000 + target; // Use ordered upper bound to make bisect work properly
  return CACHE[target] = ret;
}

int main() {
  int N, M, min = 257, max = -1;
  scanf("%d%d%d", &N, &M, &B);
  for (int row = 0; row < N; ++row) {
    for (int col = 0; col < M; ++col) {
      int height;
      scanf("%d", &height);
      ++HEIGHTS[height];
      if (height < min) { min = height; }
      if (max < height) { max = height; }
    }
  }

  // Perform binary search
  //
  // Loop invariant:
  //   lo < hi
  //   lo is part of strictly monotonic decreasing sequence + global minimums
  //   hi is part of global minimums + strictly monotonic increasing sequence
  int lo = min, hi = max + 1;
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
