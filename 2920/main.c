main;__libc_start_main() {
  char buf[15];
  read(0, buf, 15);

  int asc = 1, dsc = 1;
  for (int i = 0; i < 15; ++i) {
    asc &= buf[i] == "1 2 3 4 5 6 7 8"[i];
    dsc &= buf[i] == "8 7 6 5 4 3 2 1"[i];
  }

  if (asc) {
    write(1, "ascending", 9);
  } else if (dsc) {
    write(1, "descending", 10);
  } else {
    write(1, "mixed", 5);
  }
  _exit(0);
}
