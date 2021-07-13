#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

int main() {
  char buffer[1000000];
  const ssize_t size = read(0, buffer, 1000000);

  size_t count = 0;

  // state
  bool was_char = false;
  for (int i = 0; i < size; ++i) {
    bool is_char = buffer[i] >= 'A';
    count += is_char && !was_char;
    was_char = is_char;
  }

  printf("%lu\n", count);
}
