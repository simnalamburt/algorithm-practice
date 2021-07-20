char *PTR;
scan() {
  int n = 0, c;
  while ((c = *PTR++) >= '0') { n = 10*n + c - '0'; }
  return n;
}

char *WPTR;
print(n) {
  if (n < 0) { *WPTR++ = '-'; print(-n); return; }
  if (n/10) { print(n/10); }
  *WPTR++ = '0' + n%10;
}

cmd(char *l) {
  char *r = PTR;
  for (; *l; ++l, ++r) { if (*l != *r) { return 0; } }
  return 1;
}

main;__libc_start_main() {
  char buf[1024 * 64], wbuf[1024 * 32];
  read(0, buf, 1024 * 64);
  PTR = buf, WPTR = wbuf;

  int N = scan(), Q[N], begin = 0, end = 0;
  for (int _ = 0; _ < N; ++_) {
    if (cmd("push")) { PTR += 5; Q[end++] = scan(); continue; }
    else if (cmd("pop")) { PTR += 4; print(begin != end ? Q[begin++] : -1); }
    else if (cmd("size")) { PTR += 5; print(end - begin); }
    else if (cmd("empty")) { PTR += 6; print(begin == end); }
    else if (cmd("front")) { PTR += 6; print(begin != end ? Q[begin] : -1); }
    else if (cmd("back")) { PTR += 5; print(begin != end ? Q[end - 1] : -1); }
    *WPTR++ = '\n';
  }

  write(1, wbuf, WPTR - wbuf);
  _exit(0);
}
