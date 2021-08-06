#include <stdio.h>

int main() {
  char BUF[64];

  int M;
  fgets(BUF, sizeof BUF, stdin);
  sscanf(BUF, "%d", &M);

  int bitset = 0;
  for (int _ = 0; _ < M; ++_) {
    fgets(BUF, sizeof BUF, stdin);
    int C = 0;

    int x;
    if (BUF[C] == 'a' && BUF[C+1] == 'd') { // add
      C += 4;

      sscanf(&BUF[C], "%d", &x);
      bitset |= (1 << x);
    } else if (BUF[C] == 'r') { // remove
      C += 7;

      sscanf(&BUF[C], "%d", &x);
      bitset &= ~(1 << x);
    } else if (BUF[C] == 'c') { // check
      C += 6;

      sscanf(&BUF[C], "%d", &x);
      printf("%d\n", !!(bitset & (1 << x)));
    } else if (BUF[C] == 't') { // toggle
      C += 7;

      sscanf(&BUF[C], "%d", &x);
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
