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
  char buf[400000];
  BUF = WBUF = buf;
  read(0, buf, 400000);

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
