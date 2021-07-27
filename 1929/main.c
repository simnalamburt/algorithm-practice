#include <unistd.h>

char BUF[16];
int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

char WBUF[538468];
int W = 0;
inline static void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  WBUF[W++] = '0' + n%10;
}

inline static _Bool nth(__uint8_t bitset[], int n) {
  return bitset[n/8] & (1 << (n%8));
}

inline static void set(__uint8_t bitset[], int n) {
  bitset[n/8] |= 1 << (n%8);
}

int main() {
  read(0, BUF, sizeof BUF);

  int M = scan_uint(), L = scan_uint() + 1;
  __uint8_t inverted_sieve[L/8 + 1];
  inverted_sieve[0] = 3;
  for (int i = 1; i < L/8 + 1; ++i) { inverted_sieve[i] = 0; }
  for (int i = 2; i*i < L; ++i) {
    if (nth(inverted_sieve, i)) { continue; }
    for (int j = i*i; j < L; j += i) { set(inverted_sieve, j); }
  }
  for (int i = M; i < L; ++i) {
    if (nth(inverted_sieve, i)) { continue; }
    print_uint(i);
    WBUF[W++] = '\n';
  }

  write(1, WBUF, W);
  _exit(0);
}
