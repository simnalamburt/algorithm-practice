#pragma GCC optimize("O4,unroll-loops")
#pragma GCC target("arch=haswell")
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

int buf[8001];

int main() { }
int __libc_start_main() {
  read(0, BUF, sizeof BUF);

  int N = scan_int(), sum = 0, min = 4001, max = -4001, *freq = &buf[4000];
  for (int i = 0; i < N; ++i) {
    int n = scan_int();

    sum += n;
    ++freq[n];
    if (n < min) { min = n; }
    if (max < n) { max = n; }
  }

  double mean = (double)sum/(double)N;
  int rounded_mean = mean + (mean > 0.0 ? 0.5 : -0.5);

  int median = 4001, remain = N/2;
  for (int i = -4000; i <= 4000; ++i) {
    remain -= freq[i];
    if (remain < 0) {
      median = i;
      break;
    }
  }

  int max_freq = 0, mode1 = 4001, mode2 = 4001;
  for (int i = -4000; i <= 4000; ++i) {
    if (max_freq < freq[i]) {
      max_freq = freq[i];
    }
  }
  for (int i = -4000; i <= 4000; ++i) {
    if (freq[i] != max_freq) { continue; }
    if (mode1 == 4001) { mode1 = i; }
    else { mode2 = i; break; }
  }
  int mode = mode2 == 4001 ? mode1 : mode2;

  int range = max - min;

  print_int(rounded_mean);
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
