#include <unistd.h>

int main(){}

int itoa(int n, char buffer[]) {
  int size = 0;
  if (n >= 10) {
    size += itoa(n/10, buffer);
  }
  buffer[size] = n%10 + '0';
  return size + 1;
}

// buffered IO
char *BUFFER;
int cursor = 65536;
int end = 65536;
char read_char() {
  if (cursor == end) {
    if (end == 65536) {
      cursor = 0;
      end = read(0, BUFFER, 65536);
    } else {
      return 0;
    }
  }

  return BUFFER[cursor++];
}

__attribute__((noreturn)) int __libc_start_main() {
  // Initialize buffer
  char buffer[65536];
  BUFFER = buffer;

  // state
  int was_char = 0, count = 0;
  for (char ch; (ch = read_char()) != 0;) {
    int is_char = ch >= 'A';
    count += is_char && !was_char;
    was_char = is_char;
  }

  // print
  int size = itoa(count, buffer);
  write(1, buffer, size);
  _exit(0);
}
