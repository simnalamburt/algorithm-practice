#include <unistd.h>

char BUF[99];

int I = 0;
int scan_uint() {
  int n = 0;
  for (;;) {
    int ch = BUF[I++];
    if (ch < '0') { return n; }
    n = 10*n + ch - '0';
  }
}

int W = 0;
void print_uint(int n) {
  if (n >= 10) { print_uint(n/10); }
  BUF[W++] = '0' + n%10;
}

int main() { }

int __libc_start_main() {
  read(0, BUF, 99);

  int x = scan_uint(), y = scan_uint(), w = scan_uint(), h = scan_uint();
  int arr[4] = { x, w-x, y, h-y };
  int min = arr[0];
  for (int i = 1; i < 4; ++i) {
    if (min > arr[i]) { min = arr[i]; }
  }
  print_uint(min);

  write(1, BUF, W);
  _exit(0);
}
