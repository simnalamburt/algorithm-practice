#include <unistd.h>

#include <vector>
#include <algorithm>

namespace {
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
}

int main() {
  char buf[2200007];
  BUF = WBUF = buf;
  read(0, buf, sizeof buf);

  int N = scan_uint();

  struct meet { int start, end; };
  std::vector<meet> meetings;
  meetings.reserve(N);
  for (int i = 0; i < N; ++i) {
    int start = scan_uint();
    int end = scan_uint();
    meetings.push_back(meet { .start = start, .end = end });
  }
  std::sort(meetings.begin(), meetings.end(), [](auto A, auto B) {
    if (A.end != B.end) { return A.end <= B.end; }
    return A.start <= B.start;
  });

  int end_at = 0, count = 0;
  for (int i = 0; i < N; ++i) {
    if (end_at > meetings[i].start) { continue; }
    end_at = meetings[i].end;
    ++count;
  }

  print_uint(count);
  write(1, WBUF, W);
  _exit(0);
}
