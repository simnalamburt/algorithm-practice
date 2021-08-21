#include <unistd.h>

#include <unordered_map>
#include <string>

using std::string;
using std::unordered_map;

namespace {
  char BUF[6'300'014];
  int C = 0;
  int scan_uint() {
    int n = 0, c;
    while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
    return n;
  }

  char WBUF[2'000'000];
  int W = 0;
  void print_uint(int n) {
    if (n/10) { print_uint(n/10); }
    WBUF[W++] = '0' + n%10;
  }
}

int main() {
  read(0, BUF, sizeof BUF);
  int N = scan_uint(), M = scan_uint();

  unordered_map<string, int> DB;
  DB.reserve(N*10);
  for (int i = 0; i < N; ++i) {
    int begin = C;
    while (BUF[C++] != ' ') { }
    size_t len = C - 1 - begin;
    string site { &BUF[begin], len };

    int idx = C;
    while (BUF[C++] != '\n') { }
    DB[site] = idx;
  }
  for (int i = 0; i < M; ++i) {
    int begin = C;
    while (BUF[C++] != '\n') { }
    size_t len = C - 1 - begin;
    string site { &BUF[begin], len };

    for (int i = DB[site]; BUF[i] != '\n'; ++i) { WBUF[W++] = BUF[i]; }
    WBUF[W++] = '\n';
  }

  write(1, WBUF, W);
  _exit(0);
}
