main;__libc_start_main() {
  char B[7],t;
  read(0, B, 7);
  int i = B[0] + 10*B[1] + 100*B[2] > B[4] + 10*B[5] + 100*B[6] ? 0 : 4;
  t = B[i];
  B[i] = B[i+2];
  B[i+2] = t;
  write(1, &B[i], 3);
  _exit(0);
}
