#include <unistd.h>

char *BUF;
int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

char *WBUF;
int W = 0;
void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  WBUF[W++] = '0' + n%10;
}

static int min(int a, int b) { return a < b ? a : b; }

static int solve(int N, int K) {
  if (N >= K) { return N - K; }
  // N < K

  if (K == 1) { /* N == 0 */ return 1; }

  if (K%2 == 1) {
    return 1 + min(solve(N, K - 1), solve(N, K + 1));
  } else {
    return min(1 + solve(N, K/2), K - N);
  }
}

int main() { }
int __libc_start_main() {
  char buf[99];
  BUF = WBUF = buf;
  read(0, buf, 99);

  int N = scan_uint(), K = scan_uint();
  int answer = solve(N, K);
  print_uint(answer);

  write(1, WBUF, W);
  _exit(0);
}
