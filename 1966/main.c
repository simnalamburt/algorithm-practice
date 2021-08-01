#include <unistd.h>

char *BUF;
int C = 0;
int scan_uint() {
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
  char buf[1024 * 64];
  BUF = WBUF = buf;
  read(0, buf, sizeof buf);

  int T = scan_uint();
  for (int _ = 0; _ < T; ++_) {
    int N = scan_uint(), M = scan_uint(), docs[N];
    for (int i = 0; i < N; ++i) { docs[i] = BUF[C + i*2] - '0'; }
    C += N*2;

    int target = docs[M], count = 0, last_idx = 0;
    for (int p = 9; p >= target; --p) {
      for (int i = last_idx, j = 0; j < N; ++j) {
        int idx = (i + j)%N;
        if (docs[idx] != p) { continue; }
        ++count;
        last_idx = idx;
        if (idx == M) { break; }
      }
    }

    print_uint(count);
    WBUF[W++] = '\n';
  }

  write(1, WBUF, W);
  _exit(0);
}
