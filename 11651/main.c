#include <unistd.h>
typedef unsigned long u64;

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

inline static void swap(u64 list[], int a, int b) {
  u64 t = list[a];
  list[a] = list[b];
  list[b] = t;
}

void quicksort(u64 list[], int begin, int end) {
  if (end <= begin + 1) { return; }

  u64 pivot = list[end - 1];
  int l = begin, r = end - 1;
  // Loop invariant: list[begin:l] <= pivot < list[r:end-1]
  while (l < r) {
    if (list[l] <= pivot) { ++l; continue; }
    swap(list, l, --r);
  }
  // Invariant: l == r
  swap(list, l, end - 1);
  // Invariant: list[begin:l] <= list[l] < list[l+1:end]
  quicksort(list, begin, l);
  quicksort(list, l + 1, end);
}

u64 list[100000];

int main() { }
int __libc_start_main() {
  read(0, BUF, sizeof BUF);

  int N = scan_int();
  for (int i = 0; i < N; ++i) {
    u64 x = scan_int() + 100000, y = scan_int() + 100000;
    list[i] = x | (y << 32ul);
  }
  quicksort(list, 0, N);
  for (int i = 0; i < N; ++i) {
    print_int((int)list[i] - 100000);
    WBUF[W++] = ' ';
    print_int((int)(list[i] >> 32ul) - 100000);
    WBUF[W++] = '\n';
  }

  write(1, WBUF, W);
  _exit(0);
}
