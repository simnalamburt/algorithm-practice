main;__libc_start_main() {
  char buf[6];
  read(0, buf, 6);

  int H = 0, M = 0, i = 0, c;
  while ('0' <= (c = buf[i++])) { H = 10*H + c - '0'; }
  while ('0' <= (c = buf[i++])) { M = 10*M + c - '0'; }

  M -= 45;
  if (M < 0) { M += 60; --H; }
  if (H < 0) { H += 24; }

  i = 0;
  if (H >= 10) { buf[i++] = '0' + H/10; }
  buf[i++] = '0' + H%10;
  buf[i++] = ' ';
  if (M >= 10) { buf[i++] = '0' + M/10; }
  buf[i++] = '0' + M%10;
  write(1, buf, i);
  _exit(0);
}
