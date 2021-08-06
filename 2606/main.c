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
u128 graph[128];

int main() { }
int __libc_start_main() {
  char buf[39609];
  BUF = WBUF = buf;
  read(0, buf, sizeof buf);

  int vertex_count = scan_uint(), edge_count = scan_uint();
  for (int _ = 0; _ < edge_count; ++_) {
    u128 a = scan_uint(), b = scan_uint();
    graph[a] |= ((u128)1 << b);
    graph[b] |= ((u128)1 << a);
  }

  u128 visited = 0;

  int tasks[1000], task_count = 0;
  tasks[task_count++] = 1;
  while (task_count) {
    int task = tasks[--task_count];
    visited |= ((u128)1 << (u128)task);
    for (int i = 1; i <= vertex_count; ++i) {
      u128 mask = (u128)1 << (u128)i;
      if (!(graph[task] & mask)) { continue; }
      if (visited & mask) { continue; }
      tasks[task_count++] = i;
    }
  }

  int count = -1;
  for (; visited; visited >>= 1) { count += visited & 1; }

  print_uint(count);
  write(1, WBUF, W);
  _exit(0);
}
