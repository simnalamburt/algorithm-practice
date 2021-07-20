#pragma GCC optimize("O3")
#pragma GCC target("arch=haswell")
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

char *BUF;
int scan_int() {
  static int C = 0;
  int n = 0, sign = 1;
  for (;;) {
    int c = BUF[C++];
    switch (c) {
      case ' ':
      case '\n':
        return n * sign;
      case '-':
        sign = -1;
        break;
      default:
        n = 10*n + c - '0';
    }
  }
}

char WBUF[1024*1024*4];
int W = 0;
void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  WBUF[W++] = '0' + n%10;
}

int main() { }

int count[20000001];

int __libc_start_main() {
  // stdin 길이 측정
  struct stat stat;
  const int ret = fstat(0, &stat);
  if (ret != 0) { _exit(-1); }
  const off_t file_size = stat.st_size;

  // stdin mmap 수행
  BUF = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, 0, 0);
  if (BUF == MAP_FAILED) { _exit(-1); }


  int N = scan_int();
  for (int i = 0; i < N; ++i) {
    ++count[10000000 + scan_int()];
  }
  int M = scan_int();
  for (int i = 0; i < M; ++i) {
    print_uint(count[10000000 + scan_int()]);
    WBUF[W++] = ' ';
  }

  write(1, WBUF, W);
  _exit(0);
}
