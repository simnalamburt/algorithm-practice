#include <unistd.h>

char BUF[1100007];
int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

char WBUF[1024 * 1024 * 32];
int W = 0;
void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  WBUF[W++] = '0' + n%10;
}

int heap[100000], top;

void heap_push(int n) {
  int idx = top;
  heap[top++] = n;

  // Fix heap
  while (idx != 0) {
    int parent = (idx - 1)/2;
    if (heap[parent] < heap[idx]) {
      int t = heap[parent];
      heap[parent] = heap[idx];
      heap[idx] = t;
      idx = parent;
    } else {
      return;
    }
  }
}

int heap_pop() {
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
      child = heap[l] > heap[r] ? l : r;
    } else if (r == top) {
      child = l;
    } else { // r > len(heap), no child
      break;
    }

    if (heap[idx] < heap[child]) {
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
  read(0, BUF, sizeof BUF);

  int N = scan_uint();
  for (int i = 0; i < N; ++i) {
    int x = scan_uint();
    if (x == 0) {
      print_uint(top > 0 ? heap_pop() : 0);
      WBUF[W++] = '\n';
    } else {
      heap_push(x);
    }
  }

  write(1, WBUF, W);
  _exit(0);
}
