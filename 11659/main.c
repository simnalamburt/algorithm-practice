#pragma GCC optimize("O4,unroll-loops")
#pragma GCC target("arch=haswell")
#include <unistd.h>

static char BUF[1900014];
static int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

static int W = 0;
static void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  BUF[W++] = '0' + n%10;
}

int main() { }
int __libc_start_main() {
  read(0, BUF, sizeof BUF);

  int N = scan_uint(), M = scan_uint();
  int partialSums[N + 1];
  int partialSum = 0;
  partialSums[0] = 0;
  for (int i = 0; i < N; ++i) {
    partialSum += scan_uint();
    partialSums[i + 1] = partialSum;
  }
  // Invariant: partialSums[i] = sum(nums[..i])
  for (int _ = 0; _ < M; ++_) {
    int i = scan_uint(), j = scan_uint();
    print_uint(partialSums[j] - partialSums[i - 1]);
    BUF[W++] = '\n';
  }

  write(1, BUF, W);
  _exit(0);
}
