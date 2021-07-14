n,i,main;__libc_start_main(c) {
  char buf[5];
  read(0, buf, 5);

  while ((c = buf[i++]) != '\n') { n = 10*n + c - '0'; }

  buf[0] = '0' + !(n%4 || !(n%100) && n%400);
  write(1, buf, 1);
  _exit(0);
}
