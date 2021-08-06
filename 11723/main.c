#include <stdio.h>
#include <string.h>

int main() {
  int M;
  scanf("%d", &M);

  int bitset = 0;
  for (int _ = 0; _ < M; ++_) {
    char buf[16];
    scanf("%s", buf);

    int x;
    if (strcmp(buf, "add") == 0) {
      scanf("%d", &x);
      bitset |= (1 << x);
    } else if (strcmp(buf, "remove") == 0) {
      scanf("%d", &x);
      bitset &= ~(1 << x);
    } else if (strcmp(buf, "check") == 0) {
      scanf("%d", &x);
      printf("%d\n", !!(bitset & (1 << x)));
    } else if (strcmp(buf, "toggle") == 0) {
      scanf("%d", &x);
      bitset ^= (1 << x);
    } else if (strcmp(buf, "all") == 0) {
      bitset = 0x001FFFFE;
    } else if (strcmp(buf, "empty") == 0) {
      bitset = 0;
    }
  }
}
