#include <unistd.h>

char BUF[16];
int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

char WBUF[538468];
int W = 0;
inline static void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  WBUF[W++] = '0' + n%10;
}

int main() {
  read(0, BUF, sizeof BUF);

  int M = scan_uint(), L = scan_uint() + 1;
  _Bool sieve[L];
  sieve[0] = sieve[1] = 0;
  for (int i = 2; i < L; ++i) { sieve[i] = 1; }
  for (int i = 2; i*i < L; ++i) {
    if (!sieve[i]) { continue; }
    for (int j = i*i; j < L; j += i) { sieve[j] = 0; }
  }
  for (int i = M; i < L; ++i) {
    if (!sieve[i]) { continue; }
    print_uint(i);
    WBUF[W++] = '\n';
  }

  write(1, WBUF, W);
  _exit(0);
}
