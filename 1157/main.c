#include <unistd.h>

int main() { }
int __libc_start_main() {
  // read
  char buffer[1000000];
  int size = read(0, buffer, 1000000);

  // store
  int counter[26];
  for (int i = 0; i < size; ++i) {
    char ch = buffer[i];
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
