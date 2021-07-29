#define BUF_SIZE (1024*8)

char *BUF, WBUF[1024*2];
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
    if (ch == '(' || ch == '[') {
      stack[top++] = ch;
    } else if (ch == ')' || ch == ']') {
      if (top <= 0 || stack[top-1] != (ch == ')' ? '(' : '[')) { goto FAILED; }
      --top;
    } else if (ch == '\n') {
      return top == 0;
    }
  }
FAILED:
  while (scan_ch() != '\n');
  return 0;
}

main;__libc_start_main() {
  char buf[BUF_SIZE];
  BUF = buf;

  for (;;) {
    if (BUF[C] == '.' && BUF[C+1] == '\n') { break; }

    if (W + 4 >= sizeof WBUF) { write(1, WBUF, W); W = 0; }
    _Bool a = solve();
    *(int*)(WBUF+W) = a ? 175334777 : 683886;
    W += a ? 4 : 3;
  }

  write(1, WBUF, W);
  _exit(0);
}
