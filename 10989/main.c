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
void try_flush() {
  if (W + 10 < BUF_SIZE) { return; }
  write(1, BUF, W);
  W = 0;
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
      BUF[W++] = '0' + i;
      BUF[W++] = '\n';
      try_flush();
    }
  }
  // 2 digit
  for (; i < 100; ++i) {
    for (int j = 0; j < count[i]; ++j) {
      BUF[W++] = '0' + i/10;
      BUF[W++] = '0' + i%10;
      BUF[W++] = '\n';
      try_flush();
    }
  }
  // 3 digit
  for (; i < 1000; ++i) {
    for (int j = 0; j < count[i]; ++j) {
      BUF[W++] = '0' + i/100;
      BUF[W++] = '0' + i/10%10;
      BUF[W++] = '0' + i%10;
      BUF[W++] = '\n';
      try_flush();
    }
  }
  // 4 digit
  for (; i < 10000; ++i) {
    for (int j = 0; j < count[i]; ++j) {
      BUF[W++] = '0' + i/1000;
      BUF[W++] = '0' + i/100%10;
      BUF[W++] = '0' + i/10%10;
      BUF[W++] = '0' + i%10;
      BUF[W++] = '\n';
      try_flush();
    }
  }
  // 10000
  for (int j = 0; j < count[10000]; ++j) {
    BUF[W++] = '1';
    BUF[W++] = '0';
    BUF[W++] = '0';
    BUF[W++] = '0';
    BUF[W++] = '0';
    BUF[W++] = '\n';
    try_flush();
  }

  write(1, BUF, W);
  _exit(0);
}
