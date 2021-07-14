char *BUF;
int I;
int scan_uint() {
  int n = 0, c;
  while ('0' <= (c = BUF[I++])) { n = 10*n + c - '0'; }
  return n;
}

main;__libc_start_main() {
  char buf[6];
  BUF = buf;
  read(0, buf, 6);

  int H = scan_uint();
  int M = scan_uint();

  M -= 45;
  if (M < 0) {
    M += 60;
    H -= 1;
  }
  if (H < 0) {
    H += 24;
  }

  int i = 0;
  if (H >= 10) { buf[i++] = '0' + H/10; }
  buf[i++] = '0' + H%10;
  buf[i++] = ' ';
  if (M >= 10) { buf[i++] = '0' + M/10; }
  buf[i++] = '0' + M%10;
  write(1, buf, i);
  _exit(0);
}
