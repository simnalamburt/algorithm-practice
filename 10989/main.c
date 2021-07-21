#pragma GCC optimize("O3")
#pragma GCC target("arch=haswell")
#include <unistd.h>

#define BUF_SIZE (1024 * 4)
#define WBUF_SIZE (1024 * 4)

char *BUF;
char scan_ch() {
  static int I = BUF_SIZE;
  if (I == BUF_SIZE) { read(0, BUF, BUF_SIZE); I = 0; }
  return BUF[I++];
}

int scan_uint() {
  int n = 0;
  for (;;) {
    int ch = scan_ch();
    if (ch < '0') { return n; }
    n = 10*n + ch - '0';
  }
}

char *WBUF;
int W = 0;
void flush() {
  write(1, WBUF, W);
  W = 0;
}

void print_ch(char ch) {
  if (W == WBUF_SIZE) { flush(); }
  WBUF[W++] = ch;
}

void print_uint(int n) {
  if (n >= 10) { print_uint(n/10); }
  print_ch(n%10 + '0');
}

int main() { }

int __libc_start_main() {
  char buf[BUF_SIZE], wbuf[WBUF_SIZE];
  BUF = buf, WBUF = wbuf;

  // main
  int N = scan_uint();
  int count[10001] = {0};
  for (int i = 0; i < N; ++i) {
    ++count[scan_uint()];
  }
  for (int i = 0; i < 10001; ++i) {
    int repeat = count[i];
    for (int j = 0; j < repeat; ++j) {
      print_uint(i);
      print_ch('\n');
    }
  }

  flush();
  _exit(0);
}
