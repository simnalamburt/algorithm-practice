#pragma GCC optimize("O3")
#pragma GCC target("arch=haswell")
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

char *BUF;
int C = 0;
int scan_uint() {
  int n = 0, sign = 1, c;
  while ((c = BUF[C++]) >= '-') {
    n = 10*n + c - '0';
  }
  return n * sign;
}

char WBUF[10500000];
int W = 0;

int main() { }

int __libc_start_main() {
  // stdin 길이 측정
  struct stat stat;
  const int ret = fstat(0, &stat);
  if (ret != 0) { _exit(-1); }
  const off_t file_size = stat.st_size;

  // stdin mmap 수행
  BUF = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, 0, 0);
  if (BUF == MAP_FAILED) { _exit(-1); }


  int N = scan_uint();
  int table[200][N];
  int ends[200] = {0};
  for (int i = 0; i < N; ++i) {
    int pos = C;
    int slot = scan_uint() - 1;
    table[slot][ends[slot]++] = pos;

    while (BUF[C++] != '\n') { }
  }

  for (int i = 0; i < 200; ++i) {
    for (int j = 0; j < ends[i]; ++j) {
      int pos = table[i][j];
      char c;
      while ((c = BUF[pos++]) != '\n') {
        WBUF[W++] = c;
      }
      WBUF[W++] = '\n';
    }
  }

  write(1, WBUF, W);
  _exit(0);
}
