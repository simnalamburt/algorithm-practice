char *BUF;
int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

char *WBUF;
int W = 0;
void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  WBUF[W++] = '0' + n%10;
}

main;__libc_start_main() {
  char buf[99];
  BUF = WBUF = buf;
  read(0, buf, 99);

  int N = scan_uint(), answer = 0;
  for (int i = N > 50 ? N - 50 : 0; i < N; ++i) {
    int digitsum = i;
    for (int n = i; n; n /= 10) { digitsum += n % 10; }
    if (digitsum == N) {
      answer = i;
      break;
    }
  }
  print_uint(answer);
  write(1, WBUF, W);
  _exit(0);
}
