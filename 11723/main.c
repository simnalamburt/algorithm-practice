#include <stdio.h>

int main() {
  int M;
  scanf("%d", &M);

  int bitset = 0;
  for (int _ = 0; _ < M; ++_) {
    char buf[16];
    scanf("%s", buf);

    int x;
    if (buf[0] == 'a' && buf[1] == 'd') {
      scanf("%d", &x);
      bitset |= (1 << x);
    } else if (buf[0] == 'r') {
      scanf("%d", &x);
      bitset &= ~(1 << x);
    } else if (buf[0] == 'c') {
      scanf("%d", &x);
      printf("%d\n", !!(bitset & (1 << x)));
    } else if (buf[0] == 't') {
      scanf("%d", &x);
      bitset ^= (1 << x);
    } else if (buf[0] == 'e') {
      bitset = 0;
    } else {
      bitset = 0x001FFFFE;
    }
  }
}
