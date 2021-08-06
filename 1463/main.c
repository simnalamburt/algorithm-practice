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

int main() { }

int __libc_start_main() {
  char buf[99];
  BUF = WBUF = buf;
  read(0, buf, 99);

  int N = scan_uint();
  int DP[N + 1];
  DP[0] = DP[1] = 0;
  for (int i = 2; i <= N; ++i) {
    int min = DP[i - 1];
    if (i%3 == 0 && min > DP[i/3]) { min = DP[i/3]; }
    if (i%2 == 0 && min > DP[i/2]) { min = DP[i/2]; }
    DP[i] = min + 1;
  }

  print_uint(DP[N]);
  write(1, WBUF, W);
  _exit(0);
}
