// clang-9 -O2 -Wall -Wextra -Wpedantic -Werror -std=c11 fast.c
//
// Reference:
//   https://www.acmicpc.net/problem/9093

#include <stdio.h> // TODO: write(2) 로 대체하자
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

// Linux specific headers
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

typedef int32_t  i32;
typedef uint8_t  u8;
typedef uint64_t u64;

int main() {
  // Measure the size of stdin
  struct stat stat;
  const i32 ret = fstat(STDIN_FILENO, &stat);
  if (ret != 0) { return -1; }
  const u64 file_size = stat.st_size;

  // Perform mmap(2) to stdin
  const u8 * const addr = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
  if (addr == MAP_FAILED) { return -1; }

  u64 idx = 0;

  // Skip the first line
  for (; idx < file_size; ++idx) {
    if (addr[idx] == '\n') { break; }
  }
  ++idx;

  u64 printed_until = idx;
  for (; idx < file_size; ++idx) {
    const u8 ch = addr[idx];
    if (ch != ' ' && ch != '\n') { continue; }

    for (u64 i = idx - 1; printed_until <= i; --i) { putchar(addr[i]); }
    putchar(ch);
    printed_until = idx + 1;
  }
  if (printed_until != file_size) {
    for (u64 i = idx - 1; printed_until <= i; --i) { putchar(addr[i]); }
    putchar('\n');
  }
}
