char *PTR;

int scan_uint() {
  int n = 0;
  for (;;) {
    char c = *PTR++;
    if (c < '0') { break; }
    n = 10*n + c - '0';
  }
  return n;
}

int print_uint(int n, char buf[]) {
  int offset = 0;
  if (n/10) { offset += print_uint(n/10, buf); }
  buf[offset] = n%10 + '0';
  return offset + 1;
}

main;__libc_start_main() {
  char buffer[1024*8] = {0}, wbuffer[1024];
  read(0, buffer, 1024*8);
  PTR = buffer;

  int N = scan_uint();
  int i = 0;
  for (int _ = 0; _ < N; ++_) {
    int score = 0, combo = 1;
    for (char ch; (ch = *PTR++) != '\n';) {
      if (ch == 'O') {
        score += combo++;
      } else {
        combo = 1;
      }
    }

    i += print_uint(score, &wbuffer[i]);
    wbuffer[i++] = '\n';
  }
  write(1, wbuffer, i);
  _exit(0);
}
