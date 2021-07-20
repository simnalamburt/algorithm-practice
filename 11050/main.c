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
  char buf[6];
  read(0, buf, 6);
  PTR = buf;

  int N = scan_uint(), K = scan_uint();

  int answer = 1;
  for (int i = 0; i < K; ++i) {
    answer = answer * (N-i) / (i+1);
  }

  int size = print_uint(answer, buf);
  write(1, buf, size);
  _exit(0);
}
