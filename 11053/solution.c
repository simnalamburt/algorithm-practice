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
typedef int32_t i32;
typedef uint32_t u32;

// 틀린 입력이 절대 들어오지 않고 입력이 스펙대로만 들어온다고 가정하면 더 빠른
// atoi를 만들 수 있다.
static inline u32 parse(const u8 *addr, off_t *p_index) {
  off_t idx = *p_index;

  u32 i = 0, number = 0;
#pragma unroll 7
  for (; i < 7; ++i) {
    const i8 ch = addr[idx + i] - '0';
    // NOTE: 올바른 입력만 들어온다면, '0'보다 작은 글자는 무조건 '\n'이다
    if (ch < 0) { break; }
    number = 10*number + ch;
  }
  *p_index = idx + i + 1;
  return number;
}

// 증가하는 부분수열 기록용 배열
//
// SEQ[i] 에는 길이가 i이고 맨 뒤 항의 값이 제일 작은 부분수열의 맨 뒤 항이
// 저장되어있다.
static u32 SEQ[1000];

static inline u32 bisect_left(u32 length, u32 query) {
  u32 lo = 0;
  u32 hi = length;

  while (lo < hi) {
    const u32 mid = (lo + hi)/2;
    if (SEQ[mid] < query) {
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }

  return lo;
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
  const u32 count = parse(input, &index);

  // SEQ 에 현재 값을 어디까지 삽입했는지 저장
  u32 len = 0;

  for (u32 i = 0; i < count; ++i) {
    const u32 num = parse(input, &index);

    const u32 idx = bisect_left(len, num);
    if (idx == len) { len += 1; }
    SEQ[idx] = num;
  }

  printf("%"PRIu32"\n", len);
}
