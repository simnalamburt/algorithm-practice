main;
__libc_start_main(){
  char buf[0x10000];

  int tbl[26];
  for (int i = 0x10000;; ++i) {
    if (i == 0x10000) {
      read(0, buf, 0x10000);
      i = 0;
    }

    int ch = buf[i];
    if (ch == '\n') { break; }
    ++tbl[(ch & 0x1F) - 1];
  }

  int max = 0, idx = -1;
  for (int i = 0; i < 26; ++i) {
    if (tbl[i] > max) {
      max = tbl[i];
      idx = i;
    }
  }

  int ctr = 0;
  for (int i = 0; i < 26; ++i) {
    if (tbl[i] == max) {
      ++ctr;
    }
  }

  char ch = ctr > 1 ? '?' : idx + 'A';
  write(1, &ch, 1);
  _exit(0);
}
