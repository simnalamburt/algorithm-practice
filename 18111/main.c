#include <stdio.h>
#include <limits.h>

int cost(int N, int M, int B, int MAP[N][M], int desired_height) {
  if (desired_height > 256) {
    return INT_MAX;
  }

  int time_cost = 0;
  long block_cost = 0;

  for (int row = 0; row < N; ++row) {
    for (int col = 0; col < M; ++col) {
      int diff = MAP[row][col] - desired_height;
      if (diff > 0) {
        // higher than desired_height
        time_cost += 2 * diff;
        block_cost -= diff;
      } else if (diff < 0) {
        // lower than desired_height
        time_cost += (-diff);
        block_cost += (-diff);
      }
    }
  }

  if (block_cost > B) {
    return INT_MAX;
  }

  return time_cost;
}

int main() {
  int N, M, B;
  scanf("%d%d%d", &N, &M, &B);
  int MAP[N][M];
  for (int row = 0; row < N; ++row) {
    for (int col = 0; col < M; ++col) {
      scanf("%d", &MAP[row][col]);
    }
  }

  int lo, hi;

  //
  // Find upper bound
  //
  lo = 0;
  hi = 257;
  // Loop invariant:
  //   lo < hi
  //   cost(lo) < INT_MAX
  //   cost(hi) = INT_MAX
  while (lo + 1 < hi) {
    int mid = (lo + hi)/2;
    if (cost(N, M, B, MAP, mid) < INT_MAX) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  int upper_bound = hi;

  //
  // Find min
  //
  lo = 0;
  hi = upper_bound;
  // Loop invariant:
  //   lo < hi
  //   lo is part of strictly monotonic decreasing sequence + global minimums
  //   hi is part of global minimums + strictly monotonic increasing sequence
  while (lo + 1 < hi) {
    int mid = (lo + hi)/2;
    if (cost(N, M, B, MAP, mid - 1) >= cost(N, M, B, MAP, mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  printf("%d %d\n", cost(N, M, B, MAP, lo), lo);
}
