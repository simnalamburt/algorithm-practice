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

main;__libc_start_main() {
  char buf[611];
  read(0, buf, 611);
  PTR = buf;

  int N = scan_uint();
  int M = scan_uint();
  int cards[N];
  for (int i = 0; i < N; ++i) {
    cards[i] = scan_uint();
  }

  int max = 0;
  for (int a = 0; a < N; ++a) {
    for (int b = a + 1; b < N; ++b) {
      for (int c = b + 1; c < N; ++c) {
        int sum = cards[a] + cards[b] + cards[c];
        if (sum > M) { continue; }
        if (sum > max) { max = sum; }
      }
    }
  }

  write(1, buf, print_uint(max, buf));
  _exit(0);
}
