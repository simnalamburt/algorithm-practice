int parse_uint(char* buf) {
  int n = 0;
  for (;;) {
    char c = *buf++;
    if (c < '0') { break; }
    n = 10*n + c - '0';
  }
  return n;
}

int __libc_start_main() {
  char buf[10100];
  read(0, buf, 3);
  int N = parse_uint(buf);

  // buffer
  int i = 0;
  for (int a = 1; a <= N; ++a) {
    for (int b = 0; b < N; ++b) { buf[i++] = b < N - a ? ' ' : '*'; }
    buf[i++] = '\n';
  }

  // write
  write(1, buf, i);
  _exit(0);
}

int main;
