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

  int N = scan_uint();
  for (int i = 0; i < N; ++i) {
    int count = 0;
    for (char ch; (ch = *PTR++) != '\n';) {
      count += ch == '(' ? 1 : -1;
      if (count < 0) {
        while (*PTR++ != '\n');
        break;
      }
    }
    if (count == 0) {
      write(1, "YES\n", 4);
    } else {
      write(1, "NO\n", 3);
    }
  }
  _exit(0);
}
