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

int solve(int i) {
  if (i <= 1) { return 0; }
  int a = solve(i/3) + i%3, b = solve(i/2) + i%2;
  return (a < b ? a : b) + 1;
}

int main() { }
int __libc_start_main() {
  char buf[9];
  BUF = WBUF = buf;
  read(0, buf, 9);
  print_uint(solve(scan_uint()));
  write(1, WBUF, W);
  _exit(0);
}
