#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("arch=haswell")

#include <unistd.h>

#define BUF_SIZE (1024 * 1024 * 6)

char BUF[BUF_SIZE];
char scan_ch() {
  static int I = BUF_SIZE;
  if (I == BUF_SIZE) { read(0, BUF, BUF_SIZE); I = 0; }
  return BUF[I++];
}

int scan_uint() {
  int n = 0;
  for (int i = 0; i < 9; ++i) {
    int ch = scan_ch();
    if (ch < '0') { break; }
    n = 10*n + ch - '0';
  }
  return n;
}

int W = 0;
void flush() {
  write(1, BUF, W);
  W = 0;
}

void print_ch(char ch) {
  if (W == BUF_SIZE) { flush(); }
  BUF[W++] = ch;
}

int main() { }

int count[10001];

int __libc_start_main() {
  // main
  int N = scan_uint();
  for (int i = 0; i < N; ++i) {
    ++count[scan_uint()];
  }

  int i = 0;
  // 1 digit
  for (; i < 10; ++i) {
    for (int j = 0; j < count[i]; ++j) {
      print_ch('0' + i);
      print_ch('\n');
    }
  }
  // 2 digit
  for (; i < 100; ++i) {
    for (int j = 0; j < count[i]; ++j) {
      print_ch('0' + i/10);
      print_ch('0' + i%10);
      print_ch('\n');
    }
  }
  // 3 digit
  for (; i < 1000; ++i) {
    for (int j = 0; j < count[i]; ++j) {
      print_ch('0' + i/100);
      print_ch('0' + i/10%10);
      print_ch('0' + i%10);
      print_ch('\n');
    }
  }
  // 4 digit
  for (; i < 10000; ++i) {
    for (int j = 0; j < count[i]; ++j) {
      print_ch('0' + i/1000);
      print_ch('0' + i/100%10);
      print_ch('0' + i/10%10);
      print_ch('0' + i%10);
      print_ch('\n');
    }
  }
  // 10000
  for (int j = 0; j < count[10000]; ++j) {
    print_ch('1');
    print_ch('0');
    print_ch('0');
    print_ch('0');
    print_ch('0');
    print_ch('\n');
  }

  flush();
  _exit(0);
}
