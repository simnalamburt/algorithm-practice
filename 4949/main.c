#include <unistd.h>

char BUF[1024 * 512];
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
      BUF[W++] = 'y';
      BUF[W++] = 'e';
      BUF[W++] = 's';
      BUF[W++] = '\n';
    } else {
      BUF[W++] = 'n';
      BUF[W++] = 'o';
      BUF[W++] = '\n';
    }
  }

  // WBUF와 BUF가 쓰는 영역이 겹치지 않는다는 가정이 들어가있음
  write(1, BUF, W);
  _exit(0);
}
