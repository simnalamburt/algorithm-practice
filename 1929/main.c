#pragma GCC optimize("O4")
#pragma GCC target("arch=haswell")
#define likely(x) __builtin_expect((x), 1)
#include <unistd.h>

typedef __uint8_t u8;

char *BUF;
int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

char WBUF[1024*64];
int W = 0;
inline static void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  WBUF[W++] = '0' + n%10;
}

inline static void try_flush() {
  if (W + 15 < 1024*64) { return; }
  write(1, WBUF, W);
  W = 0;
}

inline static _Bool nth(u8 bitset[], int n) {
  return bitset[n/8] & (1 << (n%8));
}

inline static void set(u8 bitset[], int n) {
  bitset[n/8] |= 1 << (n%8);
}

u8 I_SIEVE[125001] = { 3 };

int main() { }
int __libc_start_main() {
  char buf[16];
  BUF = buf;
  read(0, buf, 16);

  int M = scan_uint(), L = scan_uint() + 1;
  for (int i = 2; i*i < L; ++i) {
    if (likely(nth(I_SIEVE, i))) { continue; }
    for (int j = i*i; j < L; j += i) { set(I_SIEVE, j); }
  }
  for (int i = M; i < L; ++i) {
    if (likely(nth(I_SIEVE, i))) { continue; }
    try_flush();
    print_uint(i);
    WBUF[W++] = '\n';
  }

  write(1, WBUF, W);
  _exit(0);
}
