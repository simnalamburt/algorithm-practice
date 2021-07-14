main;__libc_start_main() {
  char buffer[27], *p = buffer;
  read(0, buffer, 27);

  int nums[9] = {0};
  for (int i = 0; i < 9; ++i) {
    for (;;) {
      char c = *p++;
      if (c < '0') { break; }
      nums[i] = 10*nums[i] + c - '0';
    }
  }

  int max = nums[0];
  int max_idx = 0;
  for (int i = 1; i < 9; ++i) {
    if (nums[i] > max) {
      max = nums[i];
      max_idx = i;
    }
  }

  char result[4] = "00\n0";
  result[0] += max / 10;
  result[1] += max % 10;
  result[3] += max_idx + 1;
  write(1, &result[max<10], 4 - (max<10));
  _exit(0);
}
