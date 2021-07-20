#pragma GCC optimize("O3")
#pragma GCC target("arch=haswell")
#include <unistd.h>

#define BUF_SIZE (1024*4)

char *BUF, *WBUF;
int C = BUF_SIZE;
int scan_ch() {
  if (C == BUF_SIZE) { read(0, BUF, BUF_SIZE); C = 0; }
  return BUF[C++];
}

int scan_int() {
  int n = 0, sign = 1, c;
  while ((c = scan_ch()) >= '-') {
    if (c == '-') { sign = -1; }
    else { n = 10*n + c - '0'; }
  }
  return n * sign;
}

int W = 0;
void flush() {
  write(1, WBUF, W);
  W = 0;
}

void print_ch(int ch) {
  if (W == BUF_SIZE) { flush(); }
  WBUF[W++] = ch;
}

void print_int(int n) {
  if (n < 0) { print_ch('-'); print_int(-n); return; }
  if (n/10) { print_int(n/10); }
  print_ch('0' + n%10);
}

int main() { }

int count[20000001];

int __libc_start_main() {
  char buf[BUF_SIZE], wbuf[BUF_SIZE];
  BUF = buf, WBUF = wbuf;

  int N = scan_int();
  for (int i = 0; i < N; ++i) {
    ++count[10000000 + scan_int()];
  }
  int M = scan_int();
  print_int(count[10000000 + scan_int()]);
  for (int i = 1; i < M; ++i) {
    print_ch(' ');
    print_int(count[10000000 + scan_int()]);
  }
  print_ch('\n');

  flush();
  _exit(0);
}
