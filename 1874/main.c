#pragma GCC optimize("O4,unroll-loops")
#pragma GCC target("arch=haswell")
#define unlikely(x) __builtin_expect((x), 0)

#include <unistd.h>
#define BUF_SIZE (1024*16)

static char *BUF;
static inline int scan_uint() {
  static int C = BUF_SIZE;
  int remain = BUF_SIZE - C;
  if (unlikely(remain <= 15)) {
    for (int i = 0; i < remain; ++i) { BUF[i] = BUF[C + i]; }
    read(0, BUF + remain, BUF_SIZE - remain);
    C = 0;
  }

  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

int main() {
  char buf[BUF_SIZE];
  BUF = buf;

  int n = scan_uint();
  int stack[n], stack_len = 0;
  char cmds[n*2]; int cmds_len = 0;
  int upcoming = 1;
  for (int _ = 0; _ < n; ++_) {
    int X = scan_uint();
    while (X >= upcoming) {
      stack[stack_len++] = upcoming++;
      cmds[cmds_len++] = '+';
    }
    if (stack_len > 0 && stack[stack_len - 1] == X) {
      --stack_len;
      cmds[cmds_len++] = '-';
    } else {
      goto IMPOSSIBLE;
    }
  }

  int W = 0;
  for (int i = 0; i < cmds_len; ++i) {
    if (unlikely(W + 2 >= BUF_SIZE)) { write(1, BUF, W); W = 0; }
    BUF[W++] = cmds[i];
    BUF[W++] = '\n';
  }
  write(1, BUF, W);
  _exit(0);

IMPOSSIBLE:
  write(1, "NO", 2);
  _exit(0);
}
