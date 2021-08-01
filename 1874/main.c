#include <unistd.h>

char *BUF;
int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

int main() {
  char buf[588902];
  int W = 0;
  BUF = buf;
  read(0, buf, sizeof buf);

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

  for (int i = 0; i < cmds_len; ++i) {
    buf[W++] = cmds[i];
    buf[W++] = '\n';
  }
  write(1, buf, W);
  _exit(0);

IMPOSSIBLE:
  write(1, "NO", 2);
  _exit(0);
}
