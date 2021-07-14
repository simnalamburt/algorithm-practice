main;__libc_start_main() {
  char buf[50];
  read(0, buf, 50);

  unsigned long long bitset = 0;
  int a = 0, c;
  for (int i = 0; i < 10; ++i) {
    int n = 0;
    while ((c = buf[a++]) >= '0') { n = 10*n + c - '0'; }
    bitset |= 1llu << (n%42);
  }
  int count = __builtin_popcountll(bitset);
  if (count == 10) {
    write(1, "10", 2);
  } else {
    buf[0] = count + '0';
    write(1, buf, 1);
  }
  _exit(0);
}
