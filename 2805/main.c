#include <unistd.h>

char BUF[1024 * 1024 * 20];
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

int main() {
  read(0, BUF, sizeof BUF);

  int N = scan_uint();
  long M = scan_uint(), trees[N];
  for (int i = 0; i < N; ++i) { trees[i] = scan_uint(); }

  long lo = 0, hi = 1000000000;
  while (lo + 1 < hi) {
    long mid = lo + (hi - lo)/2;

    long val = 0;
    for (int i = 0; i < N; ++i) {
      if (trees[i] <= mid) { continue; }
      val += trees[i] - mid;
    }
    if (val >= M) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  print_uint(lo);
  write(1, WBUF, W);
  _exit(0);
}
