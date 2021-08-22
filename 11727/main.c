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

struct pair { int A, B; };
int solve(int n) {
  if (n == 1) { return 1; }

  struct pair state = { .A = 1, .B = 1 };
  for (int i = 2; i < n + 1; ++i) {
    state = (struct pair) { .A = state.B, .B = (2*state.A + state.B)%10007 };
  }
  return state.B;
}

int main() { }
int __libc_start_main() {
  char buf[99];
  BUF = WBUF = buf;
  read(0, buf, sizeof buf);

  int n = scan_uint();
  print_uint(solve(n));

  write(1, WBUF, W);
  _exit(0);
}
