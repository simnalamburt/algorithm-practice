#include <unistd.h>

char *PTR;

int scan_uint() {
  int n = 0, c;
  while ((c = *PTR++) >= '0') { n = 10*n + c - '0'; }
  return n;
}

int main() { }

int __libc_start_main() {
  char buf[23005], wbuf[256];
  read(0, buf, 23005);
  PTR = buf;

  int N = scan_uint();

  int I = 0;
  for (int _ = 0; _ < N; ++_) {
    int R = *PTR++ - '0';
    ++PTR;
    for (char ch; (ch = *PTR++) != '\n';) {
      for (int r = 0; r < R; ++r) {
        if (I >= 256) { _exit(0); }
        wbuf[I++] = ch;
      }
    }
    wbuf[I++] = '\n';
    write(1, wbuf, I);
    I = 0;
  }

  _exit(0);
}
