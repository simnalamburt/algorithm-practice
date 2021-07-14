#include <unistd.h>

char *PTR;
int read_uint() {
  for (int n = 0;;) {
    char ch = *PTR++;
    if ('0' <= ch && ch <= '9') {
      n = 10*n + ch - '0';
    } else {
      return n;
    }
  }
}

int __libc_start_main() {
  char buf[5150];
  read(0, buf, 9);
  PTR = buf;

  // read
  int N = read_uint();

  // buffer
  int i = 0;
  for (int a = 1; a <= N; ++a) {
    for (int b = 1; b <= a; ++b) {
      buf[i++] = '*';
    }
    buf[i++] = '\n';
  }

  // write
  write(1, buf, i);
  _exit(0);
}

int main() { }
