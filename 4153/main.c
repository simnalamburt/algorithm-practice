char *PTR;

int scan_uint() {
  int n = 0, c;
  while ((c = *PTR++) >= '0') { n = 10*n + c - '0'; }
  return n;
}

main;__libc_start_main() {
  char buf[4 * 1024];
  read(0, buf, 4 * 1024);
  PTR = buf;

  for (;;) {
    int a = scan_uint(), b = scan_uint(), c = scan_uint();
    if (!a && !b && !c) { break; }
    if (a > c) { int t = a; a = c; c = t; }
    if (b > c) { int t = b; b = c; c = t; }
    write(1, a*a + b*b == c*c ? "right\n" : "wrong\n", 6);
  }
  _exit(0);
}
