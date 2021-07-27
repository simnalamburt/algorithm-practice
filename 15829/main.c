#include <unistd.h>

char *BUF;
int C = 0;
int scan_uint() {
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
  long sum = 0;
  for (int i = N - 1; i >= 0; --i) { sum = (BUF[C+i] - 96 + sum*31)%1234567891; }
  print_uint(sum);
  write(1, WBUF, W);
  _exit(0);
}
