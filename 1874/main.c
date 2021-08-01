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
  BUF = buf;
  read(0, buf, sizeof buf);

  int n = scan_uint(), stack[n], stack_len = 0, upcoming = 1;
  char WBUF[n*4]; int W = 0;

  for (int _ = 0; _ < n; ++_) {
    int X = scan_uint();
    while (X >= upcoming) {
      stack[stack_len++] = upcoming++;
      WBUF[W++] = '+';
      WBUF[W++] = '\n';
    }
    if (stack_len > 0 && stack[stack_len - 1] == X) {
      --stack_len;
      WBUF[W++] = '-';
      WBUF[W++] = '\n';
    } else {
      goto IMPOSSIBLE;
    }
  }

  write(1, WBUF, W);
  _exit(0);

IMPOSSIBLE:
  write(1, "NO", 2);
  _exit(0);
}
