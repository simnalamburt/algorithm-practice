main;__libc_start_main() {
  char buffer[15];
  read(0, buffer, 15);

  char asc[15] = "1 2 3 4 5 6 7 8";
  char dsc[15] = "8 7 6 5 4 3 2 1";
  int is_asc = 1, is_dsc = 1;

  for (int i = 0; i < 15; ++i) {
    is_asc &= buffer[i] == asc[i];
    is_dsc &= buffer[i] == dsc[i];
  }
  if (is_asc) {
    write(1, "ascending", 9);
  } else if (is_dsc) {
    write(1, "descending", 10);
  } else {
    write(1, "mixed", 5);
  }
  _exit(0);
}
