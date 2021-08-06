#include <unistd.h>

char *BUF;
int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

char *WBUF;
int W = 0;
void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  WBUF[W++] = '0' + n%10;
}

typedef __uint128_t u128;
u128 graph[128], I = 1;

int main() { }
int __libc_start_main() {
  char buf[39609];
  BUF = WBUF = buf;
  read(0, buf, sizeof buf);

  int V = scan_uint(), E = scan_uint();
  for (int _ = 0; _ < E; ++_) {
    int a = scan_uint(), b = scan_uint();
    graph[a] |= (I << b);
    graph[b] |= (I << a);
  }

  u128 visited = 0;

  u128 tasks = 0x2;
  while (tasks) {
    int task = 0;
    for (u128 t = tasks; !(t & 1); ++task, t >>= 1) { }
    tasks &= ~(I << task);
    visited |= (I << task);
    tasks |= graph[task] & ~visited;
  }

  int count = -1;
  for (; visited; visited >>= 1) { count += visited & 1; }

  print_uint(count);
  write(1, WBUF, W);
  _exit(0);
}
