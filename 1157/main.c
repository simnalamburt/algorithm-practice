#include <unistd.h>

int main() { }
int __libc_start_main() {
  // buffered IO
  char buffer[0x10000];
  read(0, buffer, 0x10000);

  // store
  int counter[26];
  for (int i = 0;; ++i) {
    if (i == 0x10000) {
      read(0, buffer, 0x10000);
      i = 0;
    }

    char ch = buffer[i];
    if (ch == '\n') { break; }
    ch -= ch >= 'a' ? 'a' : 'A';
    ++counter[ch];
  }

  // find max
  int max_count = counter[0];
  int max_idx = 0;
  for (int i = 1; i < 26; ++i) {
    if (counter[i] > max_count) {
      max_count = counter[i];
      max_idx = i;
    }
  }

  // count max
  int count = 0;
  for (int i = 0; i < 26; ++i) {
    if (counter[i] == max_count) {
      ++count;
    }
  }

  char result = count > 1 ? '?' : max_idx + 'A';
  write(1, &result, 1);
  _exit(0);
}
