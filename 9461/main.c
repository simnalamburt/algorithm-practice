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
void print_ulong(long n) {
  if (n/10) { print_ulong(n/10); }
  WBUF[W++] = '0' + n%10;
}

int main() { }
int __libc_start_main() {
  long DP[100] = {1,1,1,2,2};
  for (int i = 5; i < 100; ++i) { DP[i] = DP[i-5] + DP[i-1]; }

  char buf[2 * 1024], wbuf[2 * 1024];
  BUF = buf;
  WBUF = wbuf;
  read(0, buf, sizeof buf);

  int T = scan_uint();
  for (int i = 0; i < T; ++i) {
    int N = scan_uint();
    print_ulong(DP[N-1]);
    WBUF[W++] = '\n';
  }

  write(1, WBUF, W);
  _exit(0);
}
