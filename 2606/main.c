#include <unistd.h>

char *BUF;
int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

typedef __uint128_t u128;
u128 graph[128], I = 1;

int main() { }
int __libc_start_main() {
  char buf[39609];
  BUF = buf;
  read(0, buf, sizeof buf);

  scan_uint();
  int E = scan_uint();
  for (int _ = 0; _ < E; ++_) {
    int a = scan_uint(), b = scan_uint();
    graph[a] |= I << b;
    graph[b] |= I << a;
  }

  u128 visited = 0, tasks = 0x2;
  while (tasks) {
    int task = 0;
    u128 T = 1;
    while (!(tasks & T)) { ++task; T <<= 1; }
    tasks &= ~T;
    visited |= T;
    tasks |= graph[task] & ~visited;
  }

  int count = -1;
  for (; visited; visited >>= 1) { count += visited & 1; }

  int W = 0;
  if (count / 10) { BUF[W++] = '0' + count/10; }
  BUF[W++] = '0' + count%10;
  write(1, BUF, W);
  _exit(0);
}
