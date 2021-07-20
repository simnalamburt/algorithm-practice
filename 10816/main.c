#pragma GCC optimize("O3")
#pragma GCC target("arch=haswell")
#include <unistd.h>

#define BUF_SIZE (1024*1024*10)
#define WBUF_SIZE (1024*1024*10)

char *BUF;
int C = 0;
int scan_int() {
  int n = 0, sign = 1, c;
  while ((c = BUF[C++]) >= '-') {
    if (c == '-') { sign = -1; }
    else { n = 10*n + c - '0'; }
  }
  return n * sign;
}

char *WBUF;
int W = 0;
void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  WBUF[W++] = '0' + n%10;
}

int main() { }

int count[20000001];

int __libc_start_main() {
  char buf[BUF_SIZE], wbuf[WBUF_SIZE];
  read(0, buf, BUF_SIZE);
  BUF = buf, WBUF = wbuf;

  int N = scan_int();
  for (int i = 0; i < N; ++i) {
    ++count[10000000 + scan_int()];
  }
  int M = scan_int();
  print_uint(count[10000000 + scan_int()]);
  for (int i = 1; i < M; ++i) {
    WBUF[W++] = ' ';
    print_uint(count[10000000 + scan_int()]);
  }
  WBUF[W++] = '\n';

  write(1, WBUF, W);
  _exit(0);
}
