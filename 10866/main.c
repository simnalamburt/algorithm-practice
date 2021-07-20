#include <unistd.h>

char *PTR;
int scan() {
  int n = 0, c;
  while ((c = *PTR++) >= '0') { n = 10*n + c - '0'; }
  return n;
}

char *WPTR;
void print(int n) {
  if (n < 0) { *WPTR++ = '-'; print(-n); return; }
  if (n/10) { print(n/10); }
  *WPTR++ = '0' + n%10;
}

int cmd(char *l) {
  char *r = PTR;
  for (; *l; ++l, ++r) { if (*l != *r) { return 0; } }
  return 1;
}

int wrap(int *p, int N) {
  *p = (*p + N)%N;
  return *p;
}

int main() { }

int __libc_start_main() {
  char buf[1024 * 90], wbuf[1024 * 32];
  read(0, buf, 1024 * 90);
  PTR = buf, WPTR = wbuf;

  int N = scan(), Deq[N], begin = 0, end = 0;
  for (int _ = 0; _ < N; ++_) {
    if (cmd("push_front")) { PTR += 11; Deq[--begin, wrap(&begin, N)] = scan(); continue; }
    else if (cmd("push_back")) { PTR += 10; Deq[end++] = scan(); wrap(&end, N); continue; }
    else if (cmd("pop_front")) { PTR += 10; print(begin != end ? Deq[begin++] : -1); wrap(&begin, N); }
    else if (cmd("pop_back")) { PTR += 9; print(begin != end ? Deq[--end, wrap(&end, N)] : -1); }
    else if (cmd("size")) { PTR += 5; print(begin <= end ? end - begin : N + end - begin); }
    else if (cmd("empty")) { PTR += 6; print(begin == end); }
    else if (cmd("front")) { PTR += 6; print(begin != end ? Deq[begin] : -1); }
    else if (cmd("back")) { PTR += 5; int back; print(begin != end ? Deq[back = end - 1, wrap(&back, N)] : -1); }
    *WPTR++ = '\n';
  }

  write(1, wbuf, WPTR - wbuf);
  _exit(0);
}
