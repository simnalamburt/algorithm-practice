// gcc solution.c -Wall -Wextra -Wpedantic -Werror -std=c17
//
// Reference:
//   https://www.acmicpc.net/problem/2751
#pragma GCC optimize("O3")
#pragma GCC target("arch=haswell")
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>

// Linux specific headers
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

typedef int32_t i32;
typedef uint8_t u8;

static i32 parse(const u8 *addr, off_t file_size, off_t *index) {
  bool is_wip = false;
  bool is_minus = false;
  i32 number_wip = 0;
  for (; *index < file_size; ++*index) {
    const u8 ch = addr[*index];

    // 올바른 입력만 들어온다는 가정 하에 이렇게 해도 됨
    if (ch == '-') {
      is_minus = true;
    }

    const bool is_num = '0' <= ch && ch <= '9';

    if (is_num) {
      number_wip = 10*number_wip + ch - '0';
      is_wip = true;
      continue;
    }

    if (is_wip) {
      // 숫자 파싱함
      return is_minus ? -number_wip : number_wip;
    }
  }

  __builtin_unreachable();
}

static int cmp(const void *a, const void *b) {
  // INT_MIN 이 입력으로 들어오지 않아서 이렇게 해도 됨
  return *(const int*)a - *(const int*)b;
}

int main() {
  // stdin 길이 측정
  struct stat stat;
  const int ret = fstat(STDIN_FILENO, &stat);
  if (ret != 0) { return -1; }
  const off_t file_size = stat.st_size;

  // stdin mmap 수행
  const u8 * const addr = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
  if (addr == MAP_FAILED) { return -1; }

  // 오토마타로 stdin 파싱
  off_t index = 0;
  const i32 count = parse(addr, file_size, &index);
  i32 numbers[count];
  for (i32 i = 0; i < count; ++i) {
    numbers[i] = parse(addr, file_size, &index);
  }

  // 정렬
  qsort(numbers, count, sizeof(i32), cmp);

  // 출력
  setvbuf(stdout, NULL, _IOFBF, 1024 * 1024);
  for (i32 i = 0; i < count; ++i) {
    printf("%"PRId32"\n", numbers[i]);
  }

  fflush(stdout);
  _exit(0);
}
