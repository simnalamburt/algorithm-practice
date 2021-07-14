int parse_uint(char buf[], int size) {
  int n = 0;
  for (int i = 0; i < size; ++i) {
    char c = buf[i];
    if (c < '0' || '9' < c) { break; }
    n = 10*n + c - '0';
  }
  return n;
}

int __libc_start_main() {
  char buf[10100];
  int size = read(0, buf, 3);
  int N = parse_uint(buf, size);

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
