#include <unistd.h>

char *BUF;
int scan_uint() {
  static int C = 0;
  int n = 0, c;
  while ((c = BUF[C++]) >= '-') { n = 10*n + c - '0'; }
  return n;
}

char *WBUF;
int W = 0;
void print_uint(int n) {
  if (n/10) { print_uint(n/10); }
  WBUF[W++] = '0' + n%10;
}

int main() {
  char buf[39609];
  BUF = WBUF = buf;
  read(0, buf, sizeof buf);

  int vertex_count = scan_uint(), edge_count = scan_uint();
  _Bool graph[vertex_count + 1][vertex_count + 1];
  for (int a = 1; a <= vertex_count; ++a) {
    for (int b = 1; b <= vertex_count; ++b) { graph[a][b] = 0; }
  }
  for (int _ = 0; _ < edge_count; ++_) {
    int a = scan_uint(), b = scan_uint();
    graph[a][b] = graph[b][a] = 1;
  }

  _Bool visited[vertex_count + 1];
  for (int i = 1; i <= vertex_count; ++i) { visited[i] = 0; }

  int tasks[1000], task_count = 0;
  tasks[task_count++] = 1;
  while (task_count) {
    int task = tasks[--task_count];
    visited[task] = 1;
    for (int i = 1; i <= vertex_count; ++i) {
      if (!graph[task][i]) { continue; }
      if (visited[i]) { continue; }
      tasks[task_count++] = i;
    }
  }

  int count = -1;
  for (int i = 1; i <= vertex_count; ++i) {
    if (!visited[i]) { continue; }
    ++count;
  }

  print_uint(count);
  write(1, WBUF, W);
  _exit(0);
}
