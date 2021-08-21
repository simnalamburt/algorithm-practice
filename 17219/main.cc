#include <unistd.h>

#include <unordered_map>
#include <string>

using std::string;
using std::unordered_map;

namespace {
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
}

int main() {
  char buf[6300014];
  BUF = WBUF = buf;
  read(0, buf, sizeof buf);

  int N = scan_uint(), M = scan_uint();

  unordered_map<string, string> DB;
  DB.reserve(N*10);
  for (int i = 0; i < N; ++i) {
    int begin = C;
    while (BUF[C++] != ' ') { }
    size_t len = C - 1 - begin;
    string site { &BUF[begin], len };

    begin = C;
    while (BUF[C++] != '\n') { }
    len = C - 1 - begin;
    string password { &BUF[begin], len };

    DB[site] = password;
  }
  for (int i = 0; i < M; ++i) {
    int begin = C;
    while (BUF[C++] != '\n') { }
    size_t len = C - 1 - begin;
    string site { &BUF[begin], len };

    for (auto ch : DB[site]) { WBUF[W++] = ch; }
    WBUF[W++] = '\n';
  }

  write(1, WBUF, W);
  _exit(0);
}
