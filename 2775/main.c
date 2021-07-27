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
  char buf[1024*16], wbuf[1024*16];
  BUF = buf;
  WBUF = wbuf;
  read(0, buf, 1024*16);

  int table[15][15] = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}};
  for (int i = 1; i < 15; ++i) {
    for (int j = 1; j < 15; ++j) {
      int sum = 0;
      for (int k = 1; k <= j; ++k) { sum += table[i-1][k]; }
      table[i][j] = sum;
    }
  }

  int N = scan_uint();
  for (int _ = 0; _ < N; ++_) {
    int k = scan_uint(), n = scan_uint();
    print_uint(table[k][n]);
    WBUF[W++] = '\n';
  }
  write(1, WBUF, W);
  _exit(0);
}
