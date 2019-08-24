// clang -std=c11 -O2 6-iterative.c -Wall -Wextra -Wpedantic -Werror

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
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

int cmp(const void *p_left, const void *p_right) {
  const u32 left = *(const u32*)p_left;
  const u32 right = *(const u32*)p_right;
  if (left < right) return +1;
  if (left > right) return -1;
  return 0;
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

  u32 coins[coins_count];
  for (u32 i = 0; i < coins_count; ++i) {
    coins[i] = parse(input, &index);
  }

  // coins 정렬
  qsort(coins, coins_count, sizeof(u32), cmp);

  // cache[] 배열 초기화
  // begin_index == coins_count - 1 인 경우에 해당함
  u32 cache[target + 1];
  for (u32 i = 0; i < target + 1; ++i) {
    cache[i] = i % coins[coins_count - 1] == 0;
  }

  // DP 수행
  for (u32 begin_index = coins_count - 2; begin_index != (u32)-1; --begin_index) {
    // begin_index : [0, coins_count - 2]

    const u32 current_coin = coins[begin_index];

    for (u32 k = target; k > 0; --k) {
      // k : [1, target]

      u32 sum = 0;
      for (u32 i = 0; i <= k/current_coin; ++i) {
        sum += cache[k - i*current_coin];
      }
      cache[k] = sum;
    }
  }

  const u32 answer = cache[target];
  printf("%"PRIu32"\n", answer);
}
