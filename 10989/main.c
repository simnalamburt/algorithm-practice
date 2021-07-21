#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("arch=haswell")

#include <unistd.h>

#define BUF_SIZE (1024 * 1024 * 6)

static char BUF[BUF_SIZE];
static int I = BUF_SIZE;
inline static void try_buffer() {
  int remain = BUF_SIZE - I;
  if (__builtin_expect(10 < remain, 1)) { return; }
  for (int i = 0; i < remain; ++i) { BUF[i] = BUF[I + i]; }
  read(0, BUF + remain, BUF_SIZE - remain);
  I = 0;
}

inline static int scan_uint() {
  try_buffer();
  int n = 0;
  for (int i = 0; i < 9; ++i) {
    int ch = BUF[I++];
    if (ch < '0') { break; }
    n = 10*n + ch - '0';
  }
  return n;
}

static int W = 0;
inline static void try_flush() {
  if (__builtin_expect(W + 10 < BUF_SIZE, 1)) { return; }
  write(1, BUF, W);
  W = 0;
}

int main() { }

static int count[10001];

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
