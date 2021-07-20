#include <unistd.h>

char *PTR;

int scan_int() {
  int n = 0, sign = 1, c;
  while ((c = *PTR++) >= '-') {
    if (c == '-') { sign = -1; }
    else { n = 10*n + c - '0'; }
  }
  return n * sign;
}

int print_int(int n, char buf[]) {
  if (n < 0) { *buf = '-'; return print_int(-n, buf+1) + 1; }
  int offset = 0;
  if (n/10) { offset += print_int(n/10, buf); }
  buf[offset] = '0' + n%10;
  return offset + 1;
}

int main() { }

int __libc_start_main() {
  char buf[1600007];
  read(0, buf, 1600007);
  PTR = buf;

  int N = scan_int();
  int x[N], y[N];
  for (int i = 0; i < N; ++i) {
    x[i] = scan_int();
    y[i] = scan_int();
  }

  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      if (x[i] < x[j] || (x[i] == x[j] && y[i] < y[j])) { continue; }

      int tx = x[i], ty = y[i];
      x[i] = x[j]; y[i] = y[j];
      x[j] = tx; y[j] = ty;
    }
  }

  int I = 0;
  for (int i = 0; i < N; ++i) {
    I += print_int(x[i], buf + I);
    buf[I++] = ' ';
    I += print_int(y[i], buf + I);
    buf[I++] = '\n';
  }
  write(1, buf, I);

  _exit(0);
}
