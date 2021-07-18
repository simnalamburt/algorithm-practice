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
    int count = 0;
    for (char ch; (ch = *PTR++) != '\n';) {
      count += ch == '(' ? 1 : -1;
      if (count < 0) {
        while (*PTR++ != '\n');
        break;
      }
    }
    if (count == 0) {
      buf[i++] = 'Y';
      buf[i++] = 'E';
      buf[i++] = 'S';
    } else {
      buf[i++] = 'N';
      buf[i++] = 'O';
    }
    buf[i++] = '\n';
  }
  write(1, buf, i);
  _exit(0);
}
