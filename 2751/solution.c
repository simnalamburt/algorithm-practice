// clang -O3 solution.c -Wall -Wextra -Wpedantic -Werror -std=c17
//
// Reference:
//   https://www.acmicpc.net/problem/2751
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
typedef uint16_t u16;
typedef uint32_t u32;

// 틀린 입력이 절대 들어오지 않고 입력이 스펙대로만 들어온다고 가정하면 더 빠른
// atoi를 만들 수 있다.
static i32 parse(const u8 *addr, off_t len, off_t *index) {
  bool is_plus = true;
  i32 number = 0;

  // NOTE: 올바른 입력만 들어온다면, addr[index]에 접근할때 바운더리 체크가 필요 없음
  if (addr[*index] == '-') {
    is_plus = false;
    *index += 1;
  }

  while (*index < len) {
    const i8 ch = addr[*index] - '0';
    // NOTE: 올바른 입력만 들어온다면, '0'보다 작은 글자는 무조건 '\n'이다
    if (ch < 0) { break; }
    number = 10*number + ch;
    *index += 1;
  }

  *index += 1;
  return is_plus ? number : -number;
}

static const char ITOA_LUT[] =
  "0001020304050607080910111213141516171819"
  "2021222324252627282930313233343536373839"
  "4041424344454647484950515253545556575859"
  "6061626364656667686970717273747576777879"
  "8081828384858687888990919293949596979899";

static bool TABLE[2000001];

// /dev/stdin 에 쓰면 불필요하게 IO로 시간 쓸까봐 .bss 에 메모리 만듬
static u8 OUTPUT_BUFFER[7888904];

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
  const i32 count = parse(input, file_size, &index);
  for (i32 i = 0; i < count; ++i) {
    const i32 num = parse(input, file_size, &index);
    // -1_000_000 <= num <= 1_000_000
    TABLE[num + 1000000] = 1;
  }

  //
  // 출력할 내용을 OUTPUT_BUFFER에 기록
  //
  u32 idx = 0;
#define ITER(BEGIN, END) for (u32 i = (BEGIN); i < (END); ++i) if (TABLE[i])
#define ASSIGN(DST, LITERAL) do { OUTPUT_BUFFER[idx + DST] = (LITERAL); } while(0)
#define MEMCPY(DST, SRC) do { memcpy(&OUTPUT_BUFFER[idx + DST], &ITOA_LUT[(SRC)*2], 2); } while(0)

  // -1_000_000
  if (TABLE[0]) {
    memcpy(&OUTPUT_BUFFER[0], "-1000000\n", 9);
    idx += 9;
  }
  // -999_999 .. -99_999
  ITER(1, 900001) {
    const u32 num = 1000000 - i;

    const u32 a = num / 10000;
    const u32 b = (num / 100) % 100;
    const u32 c = num % 100;

    ASSIGN(0, '-');
    MEMCPY(1, a);
    MEMCPY(3, b);
    MEMCPY(5, c);
    ASSIGN(7, '\n');
    idx += 8;
  }
  // -99_999 .. -9_999
  ITER(900001, 990001) {
    const u32 num = 1000000 - i;

    const u32 a = num / 10000 + '0';
    const u32 b = (num / 100) % 100;
    const u32 c = num % 100;

    ASSIGN(0, '-');
    ASSIGN(1, a);
    MEMCPY(2, b);
    MEMCPY(4, c);
    ASSIGN(6, '\n');
    idx += 7;
  }
  // -9_999 .. -999
  ITER(990001, 999001) {
    const u32 num = 1000000 - i;

    const u32 a = num / 100;
    const u32 b = num % 100;

    ASSIGN(0, '-');
    MEMCPY(1, a);
    MEMCPY(3, b);
    ASSIGN(5, '\n');
    idx += 6;
  }
  // -999 .. -99
  ITER(999001, 999901) {
    const u32 num = 1000000 - i;

    const u32 a = num / 100 + '0';
    const u32 b = num % 100;

    ASSIGN(0, '-');
    ASSIGN(1, a);
    MEMCPY(2, b);
    ASSIGN(4, '\n');
    idx += 5;
  }
  // -99 .. -9
  ITER(999901, 999991) {
    const u32 num = 1000000 - i;

    ASSIGN(0, '-');
    MEMCPY(1, num);
    ASSIGN(3, '\n');
    idx += 4;
  }
  // -9 .. 0
  ITER(999991, 1000000) {
    const u32 num = 1000000 - i;

    ASSIGN(0, '-');
    ASSIGN(1, num + '0');
    ASSIGN(2, '\n');
    idx += 3;
  }
  // 0 .. 10
  ITER(1000000, 1000010) {
    const u32 num = i - 1000000;

    ASSIGN(0, num + '0');
    ASSIGN(1, '\n');
    idx += 2;
  }
  // 10 .. 100
  ITER(1000010, 1000100) {
    const u32 num = i - 1000000;

    MEMCPY(0, num);
    ASSIGN(2, '\n');
    idx += 3;
  }
  // 100 .. 1_000
  ITER(1000100, 1001000) {
    const u32 num = i - 1000000;

    const u32 a = num / 100 + '0';
    const u32 b = num % 100;

    ASSIGN(0, a);
    MEMCPY(1, b);
    ASSIGN(3, '\n');
    idx += 4;
  }
  // 1_000 .. 10_000
  ITER(1001000, 1010000) {
    const u32 num = i - 1000000;

    const u32 a = num / 100;
    const u32 b = num % 100;

    MEMCPY(0, a);
    MEMCPY(2, b);
    ASSIGN(4, '\n');
    idx += 5;
  }
  // 10_000 .. 100_000
  ITER(1010000, 1100000) {
    const u32 num = i - 1000000;

    const u32 a = num / 10000 + '0';
    const u32 b = (num / 100) % 100;
    const u32 c = num % 100;

    ASSIGN(0, a);
    MEMCPY(1, b);
    MEMCPY(3, c);
    ASSIGN(5, '\n');
    idx += 6;
  }
  // 100_000 .. 1_000_000
  ITER(1100000, 2000000) {
    const u32 num = i - 1000000;

    const u32 a = num / 10000;
    const u32 b = (num / 100) % 100;
    const u32 c = num % 100;

    MEMCPY(0, a);
    MEMCPY(2, b);
    MEMCPY(4, c);
    ASSIGN(6, '\n');
    idx += 7;
  }
  // 1_000_000
  if (TABLE[2000000]) {
    memcpy(&OUTPUT_BUFFER[idx], "1000000", 7);
    // NOTE: 맨 마지막 줄에 LF 없어도 정답으로 인정됨
    idx += 7;
  }
#undef ITER
#undef ASSIGN
#undef MEMCPY

  //
  // 출력
  //
  write(STDOUT_FILENO, OUTPUT_BUFFER, idx);
  _exit(0);
}
