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

double sqrt(double square) {
  const double MINDIFF = 2.25e-308;
  double root = square/3.0;
  for (;;) {
    double last = root;
    root = (root + square / root) / 2;

    double diff = root - last;
    if (-MINDIFF <= diff && diff <= MINDIFF) { return root; }
  }
}

int solve(int n) {
  int upper_bound = (int)(sqrt(n) + 1.5);
  for (int b = 0; b < upper_bound; ++b) {
    for (int c = b; c < upper_bound; ++c) {
      for (int d = c; d < upper_bound; ++d) {
        if (b*b + c*c + d*d != n) { continue; }
        if (c == 0) { return 1; }
        if (b == 0) { return 2; }
        return 3;
      }
    }
  }
  return 4;
}

int main() { }
int __libc_start_main() {
  char buf[99];
  BUF = WBUF = buf;
  read(0, buf, 99);

  int n = scan_uint();
  int answer = solve(n);
  print_uint(answer);

  write(1, WBUF, W);
  _exit(0);
}
