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

int main() {
  char buffer[1024*32];
  read(0, buffer, 1024*8);
  PTR = buffer;

  int N = scan_uint();
  int i = 0;
  for (int _ = 0; _ < N; ++_) {
    int sum = PTR[0] - '0' + PTR[2] - '0';
    if (sum >= 10) {
      buffer[i++] = '1';
      buffer[i++] = '0' + sum - 10;
      buffer[i++] = '\n';
    } else {
      buffer[i++] = '0' + sum;
      buffer[i++] = '\n';
    }
    PTR += 4;
  }

  write(1, buffer, i);
  _exit(0);
}
