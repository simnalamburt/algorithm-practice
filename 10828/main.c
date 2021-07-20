#include <unistd.h>

char *PTR;

int scan_uint() {
  int n = 0, c;
  while ((c = *PTR++) >= '0') { n = 10*n + c - '0'; }
  return n;
}

int print_uint(int n, char buf[]) {
  int offset = 0;
  if (n/10) { offset += print_uint(n/10, buf); }
  buf[offset] = '0' + n%10;
  return offset + 1;
}

_Bool is_equal(char left[], char right[]) {
  for (int i = 0; left[i]; ++i) {
    if (left[i] != right[i]) { return 0; }
  }
  return 1;
}

int main() { }

int __libc_start_main() {
  char buf[120006], wbuf[70000];
  read(0, buf, 120006);
  PTR = buf;

  int N = scan_uint(), i = 0, stack[N], top = 0;
  for (int _ = 0; _ < N; ++_) {
    if (is_equal("push", PTR)) {
      PTR += 5;

      stack[top++] = scan_uint();
    } else if (is_equal("pop", PTR)) {
      PTR += 4;

      if (!top) {
        wbuf[i++] = '-';
        wbuf[i++] = '1';
      } else {
        i += print_uint(stack[--top], &wbuf[i]);
      }
      wbuf[i++] = '\n';
    } else if (is_equal("size", PTR)) {
      PTR += 5;

      i += print_uint(top, &wbuf[i]);
      wbuf[i++] = '\n';
    } else if (is_equal("empty", PTR)) {
      PTR += 6;

      i += print_uint(!top, &wbuf[i]);
      wbuf[i++] = '\n';
    } else if (is_equal("top", PTR)) {
      PTR += 4;

      if (!top) {
        wbuf[i++] = '-';
        wbuf[i++] = '1';
      } else {
        i += print_uint(stack[top-1], &wbuf[i]);
      }
      wbuf[i++] = '\n';
    }
  }

  write(1, wbuf, i);
  _exit(0);
}
