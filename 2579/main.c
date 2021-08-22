#include <unistd.h>

char BUF[1804];
int C, W;
int scan_uint() {
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}
void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  BUF[W++] = '0' + n%10;
}

int solve(int val[], int len) {
  if (len == 1) { return val[0]; }
  if (len == 2) { return val[0] + val[1]; }

  int DP[len + 1];
  DP[0] = 0;
  DP[1] = val[0];
  DP[2] = val[0] + val[1];

  for (int i = 3; i <= len; ++i) {
    int a = DP[i-2] + val[i-1];
    int b = DP[i-3] + val[i-2] + val[i-1];
    DP[i] = a > b ? a : b;
  }

  return DP[len];
}

int main() { }
int __libc_start_main() {
  read(0, BUF, sizeof BUF);

  int N = scan_uint(), stairs[N];
  for (int i = 0; i < N; ++i) { stairs[i] = scan_uint(); }
  print_uint(solve(stairs, N));
  write(1, BUF, W);
  _exit(0);
}
