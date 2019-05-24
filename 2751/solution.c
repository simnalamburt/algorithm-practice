// clang -O2 solution.c -lm -static -Wall -Wextra -Wpedantic -Werror -std=c11
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
static inline i32 parse(const u8 *addr, off_t *p_index) {
  off_t idx = *p_index;

  // NOTE: 올바른 입력만 들어온다면, addr[index]에 접근할때 바운더리 체크가 필요 없음
  const bool is_plus = addr[idx] != '-';
  if (!is_plus) { idx += 1; }

  i32 i = 0, number = 0;
#pragma unroll 7
  for (; i < 7; ++i) {
    const i8 ch = addr[idx + i] - '0';
    // NOTE: 올바른 입력만 들어온다면, '0'보다 작은 글자는 무조건 '\n'이다
    if (ch < 0) { break; }
    number = 10*number + ch;
  }
  *p_index = idx + i + 1;
  return is_plus ? number : -number;
}

static const char ITOA_LUT[] =
  "0001020304050607080910111213141516171819"
  "2021222324252627282930313233343536373839"
  "4041424344454647484950515253545556575859"
  "6061626364656667686970717273747576777879"
  "8081828384858687888990919293949596979899";

static bool TABLE[2000001];

// 출력을 큰 메모리영역에 버퍼링한다음, 한번의 write(2) 콜로 출력함
// 원래는 mmap(/dev/stdin) 에 버퍼링을 했었는데, 거기에 쓰면 불필요하게 IO Queue
// 생길까봐 .bss에 따로 메모리를 할당하는 구현으로 바꿈
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
  const i32 count = parse(input, &index);
  for (i32 i = 0; i < count; ++i) {
    const i32 num = parse(input, &index);
    // -1_000_000 <= num <= 1_000_000
    TABLE[num + 1000000] = 1;
  }

  //
  // 출력할 내용을 OUTPUT_BUFFER에 기록
  //
  u32 idx = 0;
  u32 i = 1;
#define ITER(BEGIN, END) for (u32 i = (BEGIN); i < (END); ++i) if (TABLE[i])
#define ASSIGN(DST, LITERAL) do { OUTPUT_BUFFER[idx + DST] = (LITERAL); } while(0)
#define MEMCPY(DST, SRC) do { memcpy(&OUTPUT_BUFFER[idx + DST], &ITOA_LUT[(SRC)*2], 2); } while(0)

  // -1_000_000
  if (TABLE[0]) {
    memcpy(&OUTPUT_BUFFER[0], "-1000000\n", 9);
    idx += 9;
  }

  // -999_999 .. -99_999
  for (i8 a = 99; a >= 10; --a) {
    for (i8 b = 99; b >= 0; --b) {
#pragma unroll 16
      for (i8 c = 99; c >= 0; --c) {
        if (!TABLE[i++]) { continue; }
        ASSIGN(0, '-');
        MEMCPY(1, a);
        MEMCPY(3, b);
        MEMCPY(5, c);
        ASSIGN(7, '\n');
        idx += 8;
      }
    }
  }

  // -99_999 .. -9_999
  for (i8 a = '9'; a >= '1'; --a) {
    for (i8 b = 99; b >= 0; --b) {
#pragma unroll 16
      for (i8 c = 99; c >= 0; --c) {
        if (!TABLE[i++]) { continue; }
        ASSIGN(0, '-');
        ASSIGN(1, a);
        MEMCPY(2, b);
        MEMCPY(4, c);
        ASSIGN(6, '\n');
        idx += 7;
      }
    }
  }

  for (i8 b = 99; b >= 10; --b) {
#pragma unroll 16
    for (i8 c = 99; c >= 0; --c) {
      if (!TABLE[i++]) { continue; }
      ASSIGN(0, '-');
      MEMCPY(1, b);
      MEMCPY(3, c);
      ASSIGN(5, '\n');
      idx += 6;
    }
  }

  // -999 .. -99
  for (i8 b = '9'; b >= '1'; --b) {
#pragma unroll 16
    for (i8 c = 99; c >= 0; --c) {
      if (!TABLE[i++]) { continue; }
      ASSIGN(0, '-');
      ASSIGN(1, b);
      MEMCPY(2, c);
      ASSIGN(4, '\n');
      idx += 5;
    }
  }

  // -99 .. -9
#pragma unroll 16
  for (i8 c = 99; c >= 10; --c) {
    if (!TABLE[i++]) { continue; }
    ASSIGN(0, '-');
    MEMCPY(1, c);
    ASSIGN(3, '\n');
    idx += 4;
  }

  // -9 .. 0
#pragma unroll 16
  for (i8 c = '9'; c >= '1'; --c) {
    if (!TABLE[i++]) { continue; }
    ASSIGN(0, '-');
    ASSIGN(1, c);
    ASSIGN(2, '\n');
    idx += 3;
  }

  // 0 .. 10
#pragma unroll 16
  for (i8 c = '0'; c <= '9'; ++c) {
    if (!TABLE[i++]) { continue; }
    ASSIGN(0, c);
    ASSIGN(1, '\n');
    idx += 2;
  }

  // 10 .. 100
#pragma unroll 16
  for (i8 c = 10; c < 100; ++c) {
    if (!TABLE[i++]) { continue; }
    MEMCPY(0, c);
    ASSIGN(2, '\n');
    idx += 3;
  }

  // 100 .. 1_000
  for (i8 b = '1'; b <= '9'; ++b) {
#pragma unroll 16
    for (i8 c = 0; c < 100; ++c) {
      if (!TABLE[i++]) { continue; }
      ASSIGN(0, b);
      MEMCPY(1, c);
      ASSIGN(3, '\n');
      idx += 4;
    }
  }

  // 1_000 .. 10_000
  for (i8 b = 10; b < 100; ++b) {
#pragma unroll 16
    for (i8 c = 0; c < 100; ++c) {
      if (!TABLE[i++]) { continue; }
      MEMCPY(0, b);
      MEMCPY(2, c);
      ASSIGN(4, '\n');
      idx += 5;
    }
  }

  // 10_000 .. 100_000
  for (i8 a = '1'; a <= '9'; ++a) {
    for (i8 b = 0; b < 100; ++b) {
#pragma unroll 16
      for (i8 c = 0; c < 100; ++c) {
        if (!TABLE[i++]) { continue; }
        ASSIGN(0, a);
        MEMCPY(1, b);
        MEMCPY(3, c);
        ASSIGN(5, '\n');
        idx += 6;
      }
    }
  }

  // 100_000 .. 1_000_000
  for (i8 a = 10; a < 100; ++a) {
    for (i8 b = 0; b < 100; ++b) {
#pragma unroll 16
      for (i8 c = 0; c < 100; ++c) {
        if (!TABLE[i++]) { continue; }
        MEMCPY(0, a);
        MEMCPY(2, b);
        MEMCPY(4, c);
        ASSIGN(6, '\n');
        idx += 7;
      }
    }
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
