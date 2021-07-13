int itoa(int n, char buf[]) {
  int size = 0;
  if (n >= 10) {
    size += itoa(n/10, buf);
  }
  buf[size] = n%10 + '0';
  return size + 1;
}

main;
__libc_start_main() {
  // Initialize buffer
  char buffer[0x10000];
  read(0, buffer, 0x10000);

  // state
  int was_char = 0, count = 0;
  for (int i = 0;; ++i) {
    if (i == 0x10000) {
      read(0, buffer, 0x10000);
      i = 0;
    }

    char ch = buffer[i];
    if (ch == '\n') { break; }
    count   += ch != ' ' && !was_char;
    was_char = ch != ' ';
  }

  // print
  write(1, buffer, itoa(count, buffer));
  _exit(0);
}
