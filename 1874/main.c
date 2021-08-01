#include <unistd.h>
#define BUF_SIZE (1024 * 32)

char BUF[BUF_SIZE];
int scan_uint() {
  static int C = BUF_SIZE;

  int remain = BUF_SIZE - C;
  if (remain <= 15) {
    for (int i = 0; i < remain; ++i) { BUF[i] = BUF[C + i]; }
    read(0, BUF + remain, BUF_SIZE - remain);
    C = 0;
  }

  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

char WBUF[400000];
int W = 0;
void println_ch(char ch) {
  WBUF[W++] = ch;
  WBUF[W++] = '\n';
}

int stack[100000];

int main() { }
int __libc_start_main() {
  int n = scan_uint(), stack_len = 0, upcoming = 1;
  for (int _ = 0; _ < n; ++_) {
    int X = scan_uint();
    while (X >= upcoming) {
      stack[stack_len++] = upcoming++;
      println_ch('+');
    }
    if (stack_len > 0 && stack[stack_len - 1] == X) {
      --stack_len;
      println_ch('-');
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
