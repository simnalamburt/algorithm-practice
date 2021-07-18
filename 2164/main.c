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
  char buf[9];
  read(0, buf, 9);
  PTR = buf;

  int N = scan_uint();
  int answer = N == 1 ? 1 : 2*N - (1 << (32 - __builtin_clz(N-1)));

  int size = print_uint(answer, buf);
  write(1, buf, size);
  _exit(0);
}
