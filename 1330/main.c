main;__libc_start_main() {
  char buf[99];
  read(0, buf, 99);

  int n[2] = {}, i = 0;
  for (int idx = 0; idx < 2; ++idx) {
    int sign = 1;
    for (;;) {
      char ch = buf[i++];
      if (ch == '-') { sign = -1; }
      else if (ch == ' ' || ch == '\n') { n[idx] *= sign; break; }
      else { n[idx] = 10*n[idx] + ch - '0'; }
    }
  }

  if (n[0] > n[1]) { write(1, ">", 1); }
  else if (n[0] < n[1]) { write(1, "<", 1); }
  else { write(1, "==", 2); }
  _exit(0);
}
