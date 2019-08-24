// clang -O2 main.c -Wall -Wextra -Wpedantic -Werror

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

// Linux specific headers
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

typedef int8_t i8;
typedef uint8_t u8;
typedef uint32_t u32;

// 틀린 입력이 절대 들어오지 않고 입력이 스펙대로만 들어온다고 가정하면 더 빠른
// atoi를 만들 수 있다.
static inline u32 parse(const u8 *addr, off_t *p_index) {
  off_t idx = *p_index;

  u32 i = 0, number = 0;
#pragma unroll 6
  for (; i < 6; ++i) {
    const i8 ch = addr[idx + i] - '0';
    // NOTE: 올바른 입력만 들어온다면, '0'보다 작은 글자는 무조건 ' ' 혹은 '\n' 이다
    if (ch < 0) { break; }
    number = 10*number + ch;
  }
  *p_index = idx + i + 1;
  return number;
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
  const u32 coins_count = parse(input, &index);
  const u32 target = parse(input, &index);

  // counts[x]: 현재까지 입력받은 동전들을 사용해, 'x원'을 만들고자 할 때 필요한
  // 최소 동전 수. 불가능한 경우 10000 초과의 값이 저장됨.
  u32 counts[target + 1];
  counts[0] = 0;
  for (u32 i = 1; i <= target; ++i) {
    counts[i] = 10001;
  }

  for (u32 i = 0; i < coins_count; ++i) {
    const u32 coin = parse(input, &index);

    for (u32 current = coin; current <= target; ++current) {
      const u32 candidate = 1 + counts[current - coin];

      // update minimum
      if (counts[current] > candidate) {
        counts[current] = candidate;
      }
    }
  }

  const u32 answer = counts[target];
  if (answer > 10000) {
    printf("-1\n");
  } else {
    printf("%"PRIu32"\n", answer);
  }
}
