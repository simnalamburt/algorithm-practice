#pragma GCC optimize("O3")
#pragma GCC target("arch=haswell")
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

char *BUF;
int I;
int scan_uint() {
  int n = 0;
  for (;;) {
    int ch = BUF[I++];
    if (ch < '0') { return n; }
    n = 10*n + ch - '0';
  }
}

char *WBUF;
int W;
void print_uint(int n) {
  if (n >= 10) { print_uint(n/10); }
  WBUF[W++] = n%10 + '0';
}

int main() { }

int __libc_start_main() {
  // stdin 길이 측정
  struct stat stat;
  const int ret = fstat(0, &stat);
  if (ret != 0) { _exit(-1); }
  const off_t file_size = stat.st_size;

  // stdin mmap 수행
  BUF = WBUF = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, 0, 0);
  if (BUF == MAP_FAILED) { _exit(-1); }

  // main
  int N = scan_uint();
  int count[10001] = {0};
  for (int i = 0; i < N; ++i) {
    ++count[scan_uint()];
  }
  for (int i = 0; i < 10001; ++i) {
    int repeat = count[i];
    for (int j = 0; j < repeat; ++j) {
      print_uint(i);
      WBUF[W++] = '\n';
    }
  }

  write(1, WBUF, W);
  _exit(0);
}
