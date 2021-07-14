a,i,main;__libc_start_main(size) {
  char buf[1024*8];
  size = read(0, buf, 1024*8);

  while (buf[a++] >= '0');

  while (a < size) {
    int sum = buf[a] + buf[a+2] - 96;
    a += 4;

    if (sum >= 10) { buf[i++] = '1'; }
    buf[i++] = '0' + sum%10;
    buf[i++] = '\n';
  }

  write(1, buf, i);
  _exit(0);
}
