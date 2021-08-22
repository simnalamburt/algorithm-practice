#include <unistd.h>

char *BUF;
int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

char *WBUF;
int W = 0;
void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  WBUF[W++] = '0' + n%10;
}

int main() { }
int __libc_start_main() {
  char buf[1900014];
  BUF = WBUF = buf;
  read(0, buf, sizeof buf);

  int N = scan_uint(), M = scan_uint();
  int partialSums[N + 1];
  int partialSum = 0;
  partialSums[0] = 0;
  for (int i = 0; i < N; ++i) {
    partialSum += scan_uint();
    partialSums[i + 1] = partialSum;
  }
  // Invariant: partialSums[i] = sum(nums[..i])
  for (int i = 0; i < M; ++i) {
    int i = scan_uint(), j = scan_uint();
    int start = i - 1, end = j;
    int answer = partialSums[end] - partialSums[start];
    print_uint(answer);
    WBUF[W++] = '\n';
  }

  write(1, WBUF, W);
  _exit(0);
}
