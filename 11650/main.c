#pragma GCC optimize("O3")
#pragma GCC target("arch=haswell")
#include <unistd.h>

#define BUF_SIZE (1024*100)

char *BUF;
int C = BUF_SIZE;
int scan_ch() {
  if (C == BUF_SIZE) { read(0, BUF, BUF_SIZE); C = 0; }
  return BUF[C++];
}

int scan_int() {
  int n = 0, sign = 1, c;
  while ((c = scan_ch()) >= '-') {
    if (c == '-') { sign = -1; }
    else { n = 10*n + c - '0'; }
  }
  return n * sign;
}

int W = 0;
void flush() {
  write(1, BUF, W);
  W = 0;
}

void print_ch(int ch) {
  if (W == BUF_SIZE) { flush(); }
  BUF[W++] = ch;
}

void print_int(int n) {
  if (n < 0) { print_ch('-'); print_int(-n); return; }
  if (n/10) { print_int(n/10); }
  print_ch('0' + n%10);
}

int main() { }

struct pair { int x, y; };

int lt(struct pair L[], int l, int r) {
  return L[l].x < L[r].x || (L[l].x == L[r].x && L[l].y < L[r].y);
}

void swap(struct pair L[], int i, int j) {
  struct pair t = L[i];
  L[i] = L[j];
  L[j] = t;
}

void sort(struct pair L[], int begin, int end) {
  if (end <= begin + 1) { return; }

  int a = begin;
  for (int b = begin; b < end - 1; ++b) {
    if (lt(L, b, end - 1)) { swap(L, a++, b); }
  }
  swap(L, a, end - 1);

  sort(L, begin, a);
  sort(L, a+1, end);
}

int __libc_start_main() {
  char buf[BUF_SIZE];
  BUF = buf;

  int N = scan_int();
  struct pair L[N];
  for (int i = 0; i < N; ++i) {
    L[i] = (struct pair){ .x = scan_int(), .y = scan_int() };
  }

  sort(L, 0, N);

  for (int i = 0; i < N; ++i) {
    print_int(L[i].x);
    print_ch(' ');
    print_int(L[i].y);
    print_ch('\n');
  }
  flush();
  _exit(0);
}
