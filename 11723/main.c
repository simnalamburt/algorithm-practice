#include <unistd.h>
#define BUF_SIZE (1024 * 1024 * 2)
#define WBUF_SIZE (1024 * 512)

char BUF[BUF_SIZE];
int C = BUF_SIZE;

void buffer() {
  int diff = BUF_SIZE - C;
  if (diff >= 32) { return; }
  for (int i = 0; i < diff; ++i) { BUF[i] = BUF[C + i]; }
  read(0, BUF + diff, BUF_SIZE - diff);
  C = 0;
}

int scan_uint() {
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

char WBUF[WBUF_SIZE];
int W;

int main() {
  buffer();
  int M = scan_uint();

  int bitset = 0;
  for (int _ = 0; _ < M; ++_) {
    buffer();
    if (BUF[C] == 'a' && BUF[C+1] == 'd') { // add
      C += 4;
      int x = scan_uint();

      bitset |= (1 << x);
    } else if (BUF[C] == 'r') { // remove
      C += 7;
      int x = scan_uint();

      bitset &= ~(1 << x);
    } else if (BUF[C] == 'c') { // check
      C += 6;
      int x = scan_uint();

      WBUF[W++] = (bitset & (1 << x)) ? '1' : '0';
      WBUF[W++] = '\n';
      if (W >= WBUF_SIZE) { write(1, WBUF, W); W = 0; }
    } else if (BUF[C] == 't') { // toggle
      C += 7;
      int x = scan_uint();

      bitset ^= (1 << x);
    } else if (BUF[C] == 'e') { // empty
      C += 6;

      bitset = 0;
    } else { // all
      C += 4;

      bitset = 0x001FFFFE;
    }
  }

  write(1, WBUF, W);
}
