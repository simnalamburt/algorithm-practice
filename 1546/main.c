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
  char buf[4005];
  read(0, buf, 4005);
  PTR = buf;

  int N = read_uint();
  int sum = 0;
  int max = 0;
  for (int i = 0; i < N; ++i) {
    int n = read_uint();
    sum += n;
    if (n > max) { max = n; }
  }

  // NOTE: 0 < r <= 100
  double r = (double)(sum * 100) / (double)(max * N);
  buf[0] = (int)(r*1E-2)    + '0';
  buf[1] = (int)(r*1E-1)%10 + '0';
  buf[2] = (int)(r*1E+0)%10 + '0';
  buf[3] = '.';
  buf[4] = (int)(r*1E+1)%10 + '0';
  buf[5] = (int)(r*1E+2)%10 + '0';
  buf[6] = (int)(r*1E+3)%10 + '0';
  write(1, buf, 7);
  _exit(0);
}

int main() { }
