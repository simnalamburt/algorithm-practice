#include <unistd.h>

char BUF[3000010];
int scan_int() {
  static int C = 0;
  int s = 1, n = 0, c;
  while ((c = BUF[C++]) >= '-') {
    if (c == '-') { s = -1; }
    else { n = 10*n + c - '0'; }
  }
  return s * n;
}

char WBUF[1024 * 32];
int W = 0;
void print_int(int n) {
  if (n < 0) { WBUF[W++] = '-'; print_int(-n); return; }
  if (n/10) { print_int(n/10); }
  WBUF[W++] = '0' + n%10;
}

struct task { int r, c, n; } tasks[10000000];
int MAP[1000][1000];

int main() {
  read(0, BUF, sizeof BUF);

  int Width = scan_int(), H = scan_int();
  for (int r = 0; r < H; ++r) {
    for (int c = 0; c < Width; ++c) {
      MAP[r][c] = scan_int();
    }
  }
  int end = 0, begin = 0;
  for (int r = 0; r < H; ++r) {
    for (int c = 0; c < Width; ++c) {
      if (MAP[r][c] != 1) { continue; }
      tasks[end++] = (struct task) { .r = r, .c = c, .n = 1 };
    }
  }

  while (begin < end) {
    struct task t = tasks[begin++];
    int r = t.r, c = t.c, n = t.n;
    if (n != 1 && MAP[r][c] != 0) {
      continue;
    }
    MAP[r][c] = n;
    if (r > 0 && MAP[r - 1][c] == 0) {
      tasks[end++] = (struct task) { .r = r - 1, .c = c, .n = n + 1 };
    }
    if (r < H - 1 && MAP[r + 1][c] == 0) {
      tasks[end++] = (struct task) { .r = r + 1, .c = c, .n = n + 1 };
    }
    if (c > 0 && MAP[r][c - 1] == 0) {
      tasks[end++] = (struct task) { .r = r, .c = c - 1, .n = n + 1 };
    }
    if (c < Width - 1 && MAP[r][c + 1] == 0) {
      tasks[end++] = (struct task) { .r = r, .c = c + 1, .n = n + 1 };
    }
  }

  int max = 0;
  _Bool all_non_zero = 1;
  for (int r = 0; r < H; ++r) {
    for (int c = 0; c < Width; ++c) {
      if (max < MAP[r][c]) { max = MAP[r][c]; }
      all_non_zero = all_non_zero && MAP[r][c] != 0;
    }
  }

  print_int(all_non_zero ? max - 1 : -1);
  write(1, WBUF, W);
  _exit(0);
}
