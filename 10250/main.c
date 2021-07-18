char *PTR;

int scan_uint() {
  int n = 0, c;
  while ((c = *PTR++) >= '0') { n = 10*n + c - '0'; }
  return n;
}

main;__libc_start_main() {
  char buf[16 * 1024];
  read(0, buf, 16 * 1024);
  PTR = buf;

  int N = scan_uint(), i = 0;
  for (int _ = 0; _ < N; ++_) {
    int H = scan_uint();
    scan_uint();
    int N_1 = scan_uint() - 1;
    int YY = N_1%H + 1;
    int XX = N_1/H + 1;

    if (YY >= 10) { buf[i++] = '0' + YY/10; }
    buf[i++] = '0' + YY%10;
    buf[i++] = '0' + XX/10;
    buf[i++] = '0' + XX%10;
    buf[i++] = '\n';
  }

  write(1, buf, i);
  _exit(0);
}
