#pragma GCC optimize("O4,unroll-loops")
#pragma GCC target("arch=haswell")
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

static char *BUF;
static int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

static char WBUF[64];
static int W = 0;
static void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  WBUF[W++] = '0' + n%10;
}

int main() {
  // stdin 길이 측정
  struct stat stat;
  if (fstat(0, &stat) != 0) { _exit(-1); }
  // stdin mmap 수행
  BUF = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, 0, 0);
  if (BUF == MAP_FAILED) { _exit(-1); }


  int N = scan_uint();
  long M = scan_uint(), trees[N];
  for (int i = 0; i < N; ++i) { trees[i] = scan_uint(); }

  long lo = 0, hi = 1000000000;
  while (lo + 1 < hi) {
    long mid = lo + (hi - lo)/2;

    long val = 0;
    for (int i = 0; i < N; ++i) {
      if (trees[i] <= mid) { continue; }
      val += trees[i] - mid;
    }
    if (val >= M) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  print_uint(lo);
  write(1, WBUF, W);
  _exit(0);
}
