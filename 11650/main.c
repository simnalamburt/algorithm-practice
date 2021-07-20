#include <unistd.h>

char *PTR;

int scan_int() {
  int n = 0, sign = 1, c;
  while ((c = *PTR++) >= '-') {
    if (c == '-') { sign = -1; }
    else { n = 10*n + c - '0'; }
  }
  return n * sign;
}

int print_int(int n, char buf[]) {
  if (n < 0) { *buf = '-'; return print_int(-n, buf+1) + 1; }
  int offset = 0;
  if (n/10) { offset += print_int(n/10, buf); }
  buf[offset] = '0' + n%10;
  return offset + 1;
}

int main() { }

struct pair { int x, y; };

int lt(struct pair left, struct pair right) {
  return left.x < right.x || (left.x == right.x && left.y < right.y);
}

void swap(struct pair L[], int i, int j) {
  struct pair t = L[i];
  L[i] = L[j];
  L[j] = t;
}

void sort(struct pair L[], int begin, int end) {
  if (end <= begin + 1) { return; }

  struct pair pivot = L[end - 1];
  int a = begin;
  for (int b = begin; b < end - 1; ++b) {
    if (lt(L[b], pivot)) { swap(L, a++, b); }
  }
  swap(L, a, end - 1);

  sort(L, begin, a);
  sort(L, a+1, end);
}

int __libc_start_main() {
  char buf[1600007];
  read(0, buf, 1600007);
  PTR = buf;

  int N = scan_int();
  struct pair L[N];
  for (int i = 0; i < N; ++i) {
    L[i] = (struct pair){ .x = scan_int(), .y = scan_int() };
  }

  sort(L, 0, N);

  int I = 0;
  for (int i = 0; i < N; ++i) {
    I += print_int(L[i].x, buf + I);
    buf[I++] = ' ';
    I += print_int(L[i].y, buf + I);
    buf[I++] = '\n';
  }
  write(1, buf, I);

  _exit(0);
}
