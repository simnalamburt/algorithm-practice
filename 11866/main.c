#include <unistd.h>

char *PTR;

int scan_uint() {
  int n = 0, c;
  while ((c = *PTR++) >= '0') { n = 10*n + c - '0'; }
  return n;
}

int print_uint(int n, char buf[]) {
  int offset = 0;
  if (n/10) { offset += print_uint(n/10, buf); }
  buf[offset] = '0' + n%10;
  return offset + 1;
}

int main() { }

int __libc_start_main() {
  char buf[1024 * 5];
  read(0, buf, 10);
  PTR = buf;

  int N = scan_uint(), K = scan_uint();

  int circle[N], len = N, pos = -1;
  for (int i = 0; i < N; ++i) { circle[i] = i + 1; }

  int I = 0;
  buf[I++] = '<';

  while (len) {
    pos += K;
    pos = (pos + len)%len;
    int num = circle[pos];

    // circle.pop(pos);
    --len;
    for (int i = pos; i < len; ++i) {
      circle[i] = circle[i+1];
    }

    --pos;

    // print
    I += print_uint(num, buf+I);
    buf[I++] = ',';
    buf[I++] = ' ';
  }

  I -= 2;
  buf[I++] = '>';
  buf[I++] = '\n';

  write(1, buf, I);
  _exit(0);
}
