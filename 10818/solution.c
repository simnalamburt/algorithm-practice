#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

// Linux specific headers
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

typedef int8_t i8;
typedef int32_t i32;
typedef uint8_t u8;

// 틀린 입력이 절대 들어오지 않고 입력이 스펙대로만 들어온다고 가정하면 더 빠른
// atoi를 만들 수 있다.
static inline i32 parse(const u8 *addr, off_t *p_index) {
  off_t idx = *p_index;

  // NOTE: 올바른 입력만 들어온다면, addr[index]에 접근할때 바운더리 체크가 필요 없음
  const bool is_plus = addr[idx] != '-';
  if (!is_plus) { idx += 1; }

  i32 i = 0, number = 0;
#pragma unroll 7
  for (; i < 7; ++i) {
    const i8 ch = addr[idx + i] - '0';
    // NOTE: 올바른 입력만 들어온다면, '0'보다 작은 글자는 무조건 '\n' 혹은 ' '
    if (ch < 0) { break; }
    number = 10*number + ch;
  }
  *p_index = idx + i + 1;
  return is_plus ? number : -number;
}

int main() {
  //
  // stdin 길이 측정
  //
  struct stat stat;
  const int ret = fstat(STDIN_FILENO, &stat);
  if (ret != 0) { return -1; }
  const off_t file_size = stat.st_size;

  //
  // stdin mmap 수행
  //
  u8 * const input = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, STDIN_FILENO, 0);
  if (input == MAP_FAILED) { return -1; }

  //
  // 오토마타로 stdin 파싱
  //
  off_t index = 0;
  const i32 count = parse(input, &index);
  i32 minimum = +1000001;
  i32 maximum = -1000001;
  for (i32 i = 0; i < count; ++i) {
    const i32 num = parse(input, &index);
    // -1_000_000 <= num <= 1_000_000

    if (minimum > num) { minimum = num; }
    if (maximum < num) { maximum = num; }
  }

  printf("%d %d\n", minimum, maximum);
}
