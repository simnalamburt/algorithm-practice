#include <unistd.h>

char BUF[1600007];
int scan_int() {
  static int C = 0;
  int n = 0, s = 1, c;
  while ((c = BUF[C++]) >= '-') {
    if (c != '-') { n = 10*n + c - '0'; }
    else { s = -1; };
  }
  return n * s;
}

char *WBUF = BUF;
int W = 0;
void print_int(int n) {
  if (n < 0) { WBUF[W++] = '-'; print_int(-n); return; }
  if (n/10) { print_int(n/10); }
  WBUF[W++] = '0' + n%10;
}

struct pair { int x, y; } list[100000];

_Bool lte(struct pair l, struct pair r) {
  return l.y != r.y ? l.y <= r.y : l.x <= r.x;
}

void swap(struct pair list[], int a, int b) {
  struct pair t = list[a];
  list[a] = list[b];
  list[b] = t;
}

void quicksort(struct pair list[], int begin, int end) {
  if (end <= begin + 1) { return; }

  struct pair pivot = list[end - 1];
  int l = begin, r = end - 1;
  // Loop invariant: list[begin:l] <= pivot < list[r:end-1]
  while (l < r) {
    if (lte(list[l], pivot)) { ++l; continue; }
    swap(list, l, --r);
  }
  // Invariant: l == r
  swap(list, l, end - 1);
  // Invariant: list[begin:l] <= list[l] < list[l+1:end]
  quicksort(list, begin, l);
  quicksort(list, l + 1, end);
}

int main() { }
int __libc_start_main() {
  read(0, BUF, sizeof BUF);

  int N = scan_int();
  for (int i = 0; i < N; ++i) {
    list[i] = (struct pair) { .x = scan_int(), .y = scan_int() };
  }
  quicksort(list, 0, N);
  for (int i = 0; i < N; ++i) {
    print_int(list[i].x);
    WBUF[W++] = ' ';
    print_int(list[i].y);
    WBUF[W++] = '\n';
  }

  write(1, WBUF, W);
  _exit(0);
}
