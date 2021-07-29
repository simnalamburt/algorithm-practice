#include <stdio.h>
#include <string.h>

_Bool solve(const char *line) {
  char stack[100];
  int top = 0, ch;
  for (int i = 0; (ch = line[i]) != 0; ++i) {
    switch (ch) {
      case '(':
      case '[':
        stack[top++] = ch;
        break;
      case ')':
        if (top > 0 && stack[top-1] == '(') { --top; }
        else { return 0; }
        break;
      case ']':
        if (top > 0 && stack[top-1] == '[') { --top; }
        else { return 0; }
        break;
    }
  }
  return top == 0;
}

int main() {
  char line[102];
  while (fgets(line, 102, stdin), strcmp(line, ".\n") != 0) {
    puts(solve(line) ? "yes" : "no");
  }
}
