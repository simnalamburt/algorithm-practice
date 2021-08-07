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

int solve(int N, int r, int c) {
  if (r == 0 && c == 0) {
    return 0;
  }

  int half = 1 << (N - 1);
  if (r < half && c < half) {
    return solve(N - 1, r, c);
  } else if (r < half && c >= half) {
    return half*half + solve(N - 1, r, c - half);
  } else if (r >= half && c < half) {
    return 2*half*half + solve(N - 1, r - half, c);
  } else {
    return 3*half*half + solve(N - 1, r - half, c - half);
  }
}

int main() { }
int __libc_start_main() {
  char buf[99];
  BUF = WBUF = buf;
  read(0, buf, 99);

  int N = scan_uint(), r = scan_uint(), c = scan_uint();
  print_uint(solve(N, r, c));

  write(1, WBUF, W);
  _exit(0);
}
