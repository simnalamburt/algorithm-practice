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

f(n) {
  if (n == 1) { return 1; }
  if (n%2 == 0) { return 2*f(n/2); }
  else { return 2*f(n/2 + 1) - 2; }
}

main;__libc_start_main() {
  char buf[7];
  read(0, buf, 7);
  PTR = buf;

  int N = scan_uint();
  int answer = f(N);

  int size = print_uint(answer, buf);
  write(1, buf, size);
  _exit(0);
}
