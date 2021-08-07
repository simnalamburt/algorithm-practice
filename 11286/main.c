#pragma GCC optimize("O4,unroll-loops")
#pragma GCC target("arch=haswell")
#include <unistd.h>
#define BUF_SIZE (1024 * 16)
#define WBUF_SIZE (1024 * 12)

static char *BUF;
static int scan_int() {
  static int C = BUF_SIZE;

  int diff = BUF_SIZE - C;
  if (diff < 16) {
    for (int i = 0; i < diff; ++i) { BUF[i] = BUF[C + i]; }
    read(0, BUF + diff, BUF_SIZE - diff);
    C = 0;
  }

  int n = 0, s = 1, c;
  while ((c = BUF[C++]) >= '-') {
    if (c == '-') { s = -1; }
    else { n = 10*n + c - '0'; }
  }
  return s * n;
}

static char *WBUF;
static int W = 0;
static void try_flush() {
  int diff = WBUF_SIZE - W;
  if (diff >= 16) { return; }
  write(1, WBUF, W);
  W = 0;
}
static void print_int(int n) {
  if (n < 0) { WBUF[W++] = '-'; print_int(-n); return; }
  if (n/10) { print_int(n/10); }
  WBUF[W++] = '0' + n%10;
}

static int top;

static inline _Bool lt(int heap[], int li, int ri) {
  int l = heap[li], al = l > 0 ? l : -l;
  int r = heap[ri], ar = r > 0 ? r : -r;
  return al != ar ? al < ar : l < r;
}

static void heap_push(int heap[], int n) {
  int idx = top;
  heap[top++] = n;

  // Fix heap
  while (idx != 0) {
    int parent = (idx - 1)/2;
    if (lt(heap, idx, parent)) {
      int t = heap[parent];
      heap[parent] = heap[idx];
      heap[idx] = t;
      idx = parent;
    } else {
      return;
    }
  }
}

static int heap_pop(int heap[]) {
  int ret = heap[0];
  heap[0] = heap[top - 1];
  --top;

  // Fix heap
  int idx = 0;
  for (;;) {
    int l = idx*2 + 1;
    int r = idx*2 + 2;

    int child;
    if (r < top) {
      child = lt(heap, l, r) ? l : r;
    } else if (r == top) {
      child = l;
    } else { // r > len(heap), no child
      break;
    }

    if (lt(heap, child, idx)) {
      int t = heap[idx];
      heap[idx] = heap[child];
      heap[child] = t;
      idx = child;
    } else {
      break;
    }
  }

  return ret;
}

int main() { }
int __libc_start_main() {
  char buf[BUF_SIZE], wbuf[WBUF_SIZE];
  BUF = buf;
  WBUF = wbuf;

  int N = scan_int(), heap[N];
  for (int i = 0; i < N; ++i) {
    int x = scan_int();
    if (x == 0) {
      try_flush();
      print_int(top > 0 ? heap_pop(heap) : 0);
      WBUF[W++] = '\n';
    } else {
      heap_push(heap, x);
    }
  }

  write(1, WBUF, W);
  _exit(0);
}
