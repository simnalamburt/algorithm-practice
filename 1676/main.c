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
  int answer = N/5 + N/25 + N/125;
  print_uint(answer);

  write(1, WBUF, W);
  _exit(0);
}
