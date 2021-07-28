#include <unistd.h>

char BUF[3000007];
int scan_int() {
  static int C = 0;
  int n = 0, s = 1, c;
  while ((c = BUF[C++]) >= '-') {
    if (c != '-') { n = 10*n + c - '0'; }
    else { s = -1; }
  }
  return s*n;
}

char *WBUF = BUF;
int W = 0;
void print_int(int n) {
  if (n<0) { WBUF[W++] = '-'; print_int(-n); return; }
  if (n/10) { print_int(n/10); }
  WBUF[W++] = '0' + n%10;
}

int ctr[8001];

int main() { }
int __libc_start_main() {
  read(0, BUF, sizeof BUF);

  int N = scan_int(), sum = 0, min = 4000, max = -4000;
  for (int i = 0; i < N; ++i) {
    int n = scan_int();

    sum += n;
    ++ctr[n+4000];
    if (n < min) { min = n; }
    else if (max < n) { max = n; }
  }

  int mean = (int)((double)sum/(double)N + 0.5);

  int median = 4001, remain = N/2;
  for (int i = 0; i < 8001; ++i) {
    remain -= ctr[i];
    if (remain < 0) {
      median = i - 4000;
      break;
    }
  }

  int max_freq = 0;
  for (int i = 0; i < 8001; ++i) {
    if (max_freq < ctr[i]) {
      max_freq = ctr[i];
    }
  }

  int mode1 = 4001, mode2 = 4001;
  for (int i = 1; i < 8001; ++i) {
    if (max_freq != ctr[i]) { continue; }

    if (mode1 == 4001) {
      mode1 = i - 4000;
    } else {
      mode2 = i - 4000;
      break;
    }
  }
  int mode = mode2 == 4001 ? mode1 : mode2;

  int range = max - min;

  print_int(mean);
  WBUF[W++] = '\n';
  print_int(median);
  WBUF[W++] = '\n';
  print_int(mode);
  WBUF[W++] = '\n';
  print_int(range);
  WBUF[W++] = '\n';

  write(1, WBUF, W);
  _exit(0);
}
