main;__libc_start_main() {
  char buf[101];
  int size = read(0, buf, 101) - 1;

  int pos[26];
  for (int i = 0; i < 26; ++i) { pos[i] = -1; }
  for (int i = size - 1; i >= 0; --i) {
    pos[buf[i] - 'a'] = i;
  }

  int w = 0;
  for (int i = 0; i < 26; ++i) {
    int n = pos[i];
    if (n == -1) {
      buf[w++] = '-';
      buf[w++] = '1';
      buf[w++] = ' ';
    } else if (n < 10) {
      buf[w++] = '0' + n;
      buf[w++] = ' ';
    } else {
      buf[w++] = '0' + n/10;
      buf[w++] = '0' + n%10;
      buf[w++] = ' ';
    }
  }
  write(1, buf, w-1);
  _exit(0);
}
