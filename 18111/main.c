#pragma GCC optimize("O4,unroll-loops")
#pragma GCC target("arch=haswell")
#include <unistd.h>

char BUF[1000017];
int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

char *WBUF = BUF;
int W = 0;
void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  WBUF[W++] = '0' + n%10;
}

static int B, HEIGHTS[257];

static int cost(int target) {
  int get = 0, used = 0;
  for (int i = 0; i < target; ++i) { used += (target - i) * HEIGHTS[i]; }
  for (int i = target + 1; i < 257; ++i) { get += (i - target) * HEIGHTS[i]; }
  int ret = used <= B + get ?
    used + 2*get :
    2100000000 + target; // Use ordered upper bound to make bisect work properly
  return ret;
}

int main() { }
int __libc_start_main() {
  read(0, BUF, sizeof BUF);

  int N = scan_uint(), M = scan_uint();
  B = scan_uint();
  for (int row = 0; row < N; ++row) {
    for (int col = 0; col < M; ++col) {
      int height = scan_uint();
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

  print_uint(cost(lo));
  WBUF[W++] = ' ';
  print_uint(lo);
  write(1, WBUF, W);
  _exit(0);
}
