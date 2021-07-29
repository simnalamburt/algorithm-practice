#include <unistd.h>
#define BUF_SIZE (1024*8)
#define WBUF_SIZE (1024*2)

char BUF[BUF_SIZE], WBUF[WBUF_SIZE];
int C = BUF_SIZE, W = 0;

char scan_ch() {
  if (C >= BUF_SIZE) { read(0, BUF, BUF_SIZE); C = 0; }
  return BUF[C++];
}

_Bool solve() {
  char stack[100];
  int top = 0;
  for (;;) {
    char ch = scan_ch();
    switch (ch) {
      case '(':
      case '[':
        stack[top++] = ch;
        break;
      case ')':
        if (top <= 0 || stack[top-1] != '(') { goto FAILED; }
        --top;
        break;
      case ']':
        if (top <= 0 || stack[top-1] != '[') { goto FAILED; }
        --top;
        break;
      case '\n':
        return top == 0;
    }
  }
FAILED:
  while (scan_ch() != '\n');
  return 0;
}

int main() { }
int __libc_start_main() {
  for (;;) {
    if (BUF[C] == '.' && BUF[C+1] == '\n') { break; }

    if (W + 4 >= WBUF_SIZE) { write(1, WBUF, W); W = 0; }
    if (solve()) {
      WBUF[W++] = 'y';
      WBUF[W++] = 'e';
      WBUF[W++] = 's';
      WBUF[W++] = '\n';
    } else {
      WBUF[W++] = 'n';
      WBUF[W++] = 'o';
      WBUF[W++] = '\n';
    }
  }

  write(1, WBUF, W);
  _exit(0);
}
