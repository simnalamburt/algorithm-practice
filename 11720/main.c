main;__libc_start_main() {
  char buf[105];
  int size = read(0, buf, 105);

  int i = 0, sum = 0;
  while (buf[i++] >= '0');
  while (i < size - 1) {
    sum += buf[i++] - '0';
  }

  i = 0;
  if (sum >= 100) { buf[i++] = '0' + sum/100; }
  if (sum >= 10)  { buf[i++] = '0' + sum/10%10; }
  buf[i++] = '0' + sum%10;
  write(1, buf, i);
  _exit(0);
}
