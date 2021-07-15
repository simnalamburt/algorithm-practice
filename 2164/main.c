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
  char buf[7];
  read(0, buf, 7);
  PTR = buf;

  int N = scan_uint();

  int cards[N*2], start = 0, end = N;
  for (int i = 0; i < N; ++i) {
    cards[i] = i + 1;
  }
  while (end - start > 1) {
    cards[end] = cards[start + 1];
    start += 2;
    end += 1;
  }

  write(1, buf, print_uint(cards[start], buf));
  _exit(0);
}
