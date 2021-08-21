#include <unistd.h>

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

struct meet { int start, end; };

static _Bool le(struct meet array[], int a, int b) {
  struct meet A = array[a], B = array[b];
  if (A.end != B.end) { return A.end <= B.end; }
  return A.start <= B.start;
}

static void mergesort(struct meet array[], int start, int end) {
  int len = end - start;

  if (len <= 1) { return; }
  // Invariant: len = end - start >= 2

  int mid = (start + end)/2;
  mergesort(array, start, mid);
  mergesort(array, mid, end);

  struct meet merged[len];
  int i = 0, a = start, b = mid;
  while (a < mid && b < end) { merged[i++] = array[le(array, a, b) ? a++ : b++]; }
  while (a < mid) { merged[i++] = array[a++]; }
  while (b < end) { merged[i++] = array[b++]; }
  for (int i = 0; i < len; ++i) { array[start + i] = merged[i]; }
}

int main() { }
int __libc_start_main() {
  char buf[2200007];
  BUF = WBUF = buf;
  read(0, buf, sizeof buf);

  int N = scan_uint();
  struct meet meetings[N];
  for (int i = 0; i < N; ++i) {
    meetings[i] = (struct meet) { .start = scan_uint(), .end = scan_uint() };
  }
  mergesort(meetings, 0, N);

  int end_at = 0, count = 0;
  for (int i = 0; i < N; ++i) {
    if (end_at <= meetings[i].start) {
      end_at = meetings[i].end;
      ++count;
    }
  }

  print_uint(count);
  write(1, WBUF, W);
  _exit(0);
}
