#include <stdio.h>

int main() {
  int count;
  scanf("%d\n", &count);
  for (int _ = 0; _ < count; ++_) {
    char line[1001];
    fgets(line, sizeof line, stdin);

    int idx = 0;
    int printed_count = 0;
    for (; idx < sizeof line - 1; ++idx) {
      char c = line[idx];
      if (c == '\n') { break; }
      if (c != ' ') { continue; }

      // printed_count 부터 i-1 까지 거꾸로 출력
      for (int j = idx - 1; printed_count <= j; --j) { putchar(line[j]); }
      putchar(' ');
      printed_count = idx + 1;
    }
    // printed_count 부터 i-1 까지 거꾸로 출력
    for (int j = idx - 1; printed_count <= j; --j) { putchar(line[j]); }
    putchar('\n');
  }
}
