#include <stdio.h>
#include <unistd.h>

int main() {
  // read
  int N;
  scanf("%d", &N);

  // buffer
  int i = 0;
  char buf[10100];
  for (int a = 1; a <= N; ++a) {
    int b = N;
    for (; b > a; --b) { buf[i++] = ' '; }
    for (; b > 0; --b) { buf[i++] = '*'; }
    buf[i++] = '\n';
  }

  // write
  write(1, buf, i);
  _exit(0);
}
