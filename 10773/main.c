#include <unistd.h>
#define BUF_SIZE (1024*16)

char *BUF;
int scan_ch() {
  static int C = BUF_SIZE;
  if (C >= BUF_SIZE) { read(0, BUF, BUF_SIZE); C = 0; }
  return BUF[C++];
}
int scan_uint() {
  int n = 0, c;
  while ((c = scan_ch()) >= '-') { n = 10*n + c - '0'; }
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
  char buf[BUF_SIZE];
  BUF = WBUF = buf;

  int N = scan_uint();

  char stack[100000];
  int top = 0;
  for (int _ = 0; _ < N; ++_) {
    int n = scan_uint();
    if (n != 0) {
      stack[top++] = n;
    } else if (top > 0) {
      --top;
    }
  }
  int sum = 0;
  for (int i = 0; i < top; ++i) {
    sum += stack[i];
  }

  print_uint(sum);
  write(1, WBUF, W);
  _exit(0);
}
