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

__attribute__((noreturn)) int __libc_start_main() {
  char buffer[1000000];
  const int size = read(0, buffer, 1000000);

  int count = 0;

  // state
  int was_char = 0;
  for (int i = 0; i < size; ++i) {
    int is_char = buffer[i] >= 'A';
    count += is_char && !was_char;
    was_char = is_char;
  }

  int size = itoa(count, buffer);
  write(1, buffer, size);
  _exit(0);
}
