#include <unistd.h>

char BUF[1024 * 1024 * 16], WBUF[1024 * 1024 * 16];
int C = 0, W = 0;

_Bool solve() {
  char stack[100];
  int top = 0;
  for (;;) {
    char ch = BUF[C++];
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
  while (BUF[C++] != '\n');
  return 0;
}

int main() { }
int __libc_start_main() {
  read(0, BUF, sizeof BUF);

  for (;;) {
    if (BUF[C] == '.' && BUF[C+1] == '\n') { break; }
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
