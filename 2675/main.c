char *PTR;

int parse_uint() {
  int n = 0;
  for (;;) {
    char c = *PTR++;
    if (c < '0') { break; }
    n = 10*n + c - '0';
  }
  return n;
}

main() {
  char buffer[23005];
  read(0, buffer, 23005);
  PTR = buffer;

  int N = parse_uint();

  char wbuffer[161000];
  int i = 0;
  for (int _ = 0; _ < N; ++_) {
    int R = *PTR++ - '0';
    ++PTR;
    for (char ch; (ch = *PTR++) != '\n';) {
      for (int r = 0; r < R; ++r) {
        wbuffer[i++] = ch;
      }
    }
    wbuffer[i++] = '\n';
  }

  write(1, wbuffer, i);
  _exit(0);
}
