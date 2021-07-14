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

main;__libc_start_main() {
  char buffer[15];
  read(0, buffer, 15);
  PTR = buffer;

  int n = parse_uint()*parse_uint()*parse_uint();
  char result[19] = "0\n0\n0\n0\n0\n0\n0\n0\n0\n0";

  while (n) {
    ++result[(n % 10)*2];
    n /= 10;
  }

  write(1, result, 19);
  _exit(0);
}
