N,i,main;__libc_start_main() {
  char buf[1024*8], *PTR = buf;
  read(0, buf, 1024*8);

  for (;;) {
    char c = *PTR++;
    if (c < '0') { break; }
    N = 10*N + c - '0';
  }

  while (N--) {
    int sum = PTR[0] + PTR[2] - 96;
    if (sum >= 10) { buf[i++] = '1'; }
    buf[i++] = '0' + sum%10;
    buf[i++] = '\n';
    PTR += 4;
  }

  write(1, buf, i);
  _exit(0);
}
