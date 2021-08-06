#include <stdio.h>

char BUF[64];
int C;

int scan_uint() {
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

int main() {
  fgets(BUF, sizeof BUF, stdin); C = 0;
  int M = scan_uint();

  int bitset = 0;
  for (int _ = 0; _ < M; ++_) {
    fgets(BUF, sizeof BUF, stdin); C = 0;

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

      printf("%d\n", !!(bitset & (1 << x)));
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
}
