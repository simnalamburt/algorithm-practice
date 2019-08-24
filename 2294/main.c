// clang -O2 main.c -Wall -Wextra -Wpedantic -Werror

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>

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

// CACHE[x][y]: 동전 COINS[y:] 를 써서 x원을 만들 때 필요한 최소 동전 수.
// 불가능한 경우 0xFFFFFFFF가 들어있음
static u32 CACHE[10001][101];
// 총 동전 종류 갯수
static u32 COINS_COUNT;
// 동전 종류
static u32 COINS[100];

static inline u32 solve(u32 current_target, u32 begin_index) {
  // current_target: [0, TARGET]
  // begin_index: [0, COINS_COUNT]
  //
  // returns:
  //   동전 COINS[begin_index:] 들을 써서 current_target원을 만들 때 필요한
  //   최소 동전 수. 불가능한 경우 0xFFFFFFFF 반환

  // 현재 쓸 수 있는 동전의 종류 수
  const u32 length = COINS_COUNT - begin_index;
  // 현재 쓸 수 있는 동전들 가운데 맨 앞에 있는것
  const u32 current_coin = COINS[begin_index];

  // Handle base cases
  if (current_target == 0) {
    // 0 원은 0개의 동전으로 만들 수 있음
    return 0;
  }
  if (length == 0) {
    // 가진 동전이 없다면 무슨 수를 써도 양수의 금액을 만들 수 없음
    return 0xFFFFFFFF;
  }
  if (length == 1) {
    // 나누어 떨어지는 경우에만 답이 나옴
    return current_target % current_coin == 0 ?
      current_target/current_coin :
      0xFFFFFFFF;
  }

  u32 min = 0xFFFFFFFF;
  for (u32 i = 0; i < current_target/current_coin + 1; ++i) {
    const u32 result = CACHE[current_target - i*current_coin][begin_index + 1];
    if (result == 0xFFFFFFFF) {
      continue;
    }
    const u32 candidate = i + result;
    if (min > candidate) {
      min = candidate;
    }
  }
  return min;
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
  COINS_COUNT = parse(input, &index);
  const u32 target = parse(input, &index);

  for (u32 i = 0; i < COINS_COUNT; ++i) {
    COINS[i] = parse(input, &index);
  }

  // DP
  for (u32 begin_index = COINS_COUNT; begin_index != 0xFFFFFFFF; --begin_index) {
    // begin_index: [0, COINS_COUNT]

    for (u32 current_target = 0; current_target <= target; ++current_target) {
      // current_target: [0, TARGET]

      const u32 result = solve(current_target, begin_index);
      CACHE[current_target][begin_index] = result;
    }
  }

  const u32 answer = CACHE[target][0];
  if (answer == 0xFFFFFFFF) {
    printf("-1\n");
  } else {
    printf("%"PRIu32"\n", answer);
  }
}
