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

int solve(int stairs[], int len) {
  switch (len) {
    case 0: return 0;
    case 1: return stairs[0];
    case 2: return stairs[0] + stairs[1];
  }
  // Invariant: len >= 3

  // DP[i] : stairs[..i] 에서의 부분해
  int DP[len + 1];
  DP[0] = 0;
  DP[1] = stairs[0];
  DP[2] = stairs[0] + stairs[1];

  for (int i = 3; i <= len; ++i) {
    int a = DP[i - 2] + stairs[i - 1];
    int b = DP[i - 3] + stairs[i - 2] + stairs[i - 1];
    DP[i] = a > b ? a : b;
  }

  return DP[len];
}

int main() { }
int __libc_start_main() {
  char buf[1804];
  BUF = WBUF = buf;
  read(0, buf, sizeof buf);

  int N = scan_uint();
  int stairs[N];
  for (int i = 0; i < N; ++i) { stairs[i] = scan_uint(); }

  int answer = solve(stairs, N);
  print_uint(answer);

  write(1, WBUF, W);
  _exit(0);
}
