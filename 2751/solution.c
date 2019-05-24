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
  for (i8 a = 99; a >= 0; --a) {
    for (i8 b = 99; b >= 0; --b) {
      for (i8 c = 99; c >= 0; --c) {
        if (i >= 1000000 - 99999) {
          goto MINUS_6DIGITS_BREAK;
        }
        if (TABLE[i]) {
          ASSIGN(0, '-');
          MEMCPY(1, a);
          MEMCPY(3, b);
          MEMCPY(5, c);
          ASSIGN(7, '\n');
          idx += 8;
        }
        i += 1;
      }
    }
  }
MINUS_6DIGITS_BREAK:

  // -99_999 .. -9_999
  for (i8 a = '9'; a >= '0'; --a) {
    for (i8 b = 99; b >= 0; --b) {
      for (i8 c = 99; c >= 0; --c) {
        if (i >= 1000000 - 9999) {
          goto MINUS_5DIGITS_BREAK;
        }
        if (TABLE[i]) {
          ASSIGN(0, '-');
          ASSIGN(1, a);
          MEMCPY(2, b);
          MEMCPY(4, c);
          ASSIGN(6, '\n');
          idx += 7;
        }
        i += 1;
      }
    }
  }
MINUS_5DIGITS_BREAK:

  for (i8 b = 99; b >= 0; --b) {
    for (i8 c = 99; c >= 0; --c) {
      if (i >= 1000000 - 999) {
        goto MINUS_4DIGITS_BREAK;
      }
      if (TABLE[i]) {
        ASSIGN(0, '-');
        MEMCPY(1, b);
        MEMCPY(3, c);
        ASSIGN(5, '\n');
        idx += 6;
      }
      i += 1;
    }
  }
MINUS_4DIGITS_BREAK:

  // -999 .. -99
  for (i8 b = '9'; b >= '0'; --b) {
    for (i8 c = 99; c >= 0; --c) {
      if (i >= 1000000 - 99) {
        goto MINUS_3DIGITS_BREAK;
      }
      if (TABLE[i]) {
        ASSIGN(0, '-');
        ASSIGN(1, b);
        MEMCPY(2, c);
        ASSIGN(4, '\n');
        idx += 5;
      }
      i += 1;
    }
  }
MINUS_3DIGITS_BREAK:

  // -99 .. -9
  for (i8 c = 99; c >= 0; --c) {
    if (i >= 1000000 - 9) {
      goto MINUS_2DIGITS_BREAK;
    }
    if (TABLE[i]) {
      ASSIGN(0, '-');
      MEMCPY(1, c);
      ASSIGN(3, '\n');
      idx += 4;
    }
    i += 1;
  }
MINUS_2DIGITS_BREAK:

  for (i8 c = '9'; c >= '0'; --c) {
    if (i >= 1000000) {
      goto MINUS_1DIGITS_BREAK;
    }
    if (TABLE[i]) {
      ASSIGN(0, '-');
      ASSIGN(1, c);
      ASSIGN(2, '\n');
      idx += 3;
    }
    i += 1;
  }
MINUS_1DIGITS_BREAK:

  // 0 .. 10
  for (i8 c = '0'; c <= '9'; ++c) {
    if (i >= 1000000 + 10) {
      goto PLUS_1DIGITS_BREAK;
    }
    if (TABLE[i]) {
      ASSIGN(0, c);
      ASSIGN(1, '\n');
      idx += 2;
    }
    i += 1;
  }
PLUS_1DIGITS_BREAK:

  // 10 .. 100
  for (i8 c = 10; c < 100; ++c) {
    if (i >= 1000000 + 100) {
      goto PLUS_2DIGITS_BREAK;
    }
    if (TABLE[i]) {
      MEMCPY(0, c);
      ASSIGN(2, '\n');
      idx += 3;
    }
    i += 1;
  }
PLUS_2DIGITS_BREAK:

  // 100 .. 1_000
  for (i8 b = '1'; b <= '9'; ++b) {
    for (i8 c = 0; c < 100; ++c) {
      if (i >= 1000000 + 1000) {
        goto PLUS_3DIGITS_BREAK;
      }
      if (TABLE[i]) {
        ASSIGN(0, b);
        MEMCPY(1, c);
        ASSIGN(3, '\n');
        idx += 4;
      }
      i += 1;
    }
  }
PLUS_3DIGITS_BREAK:

  // 1_000 .. 10_000
  for (i8 b = 10; b < 100; ++b) {
    for (i8 c = 0; c < 100; ++c) {
      if (i >= 1000000 + 10000) {
        goto PLUS_4DIGITS_BREAK;
      }
      if (TABLE[i]) {
        MEMCPY(0, b);
        MEMCPY(2, c);
        ASSIGN(4, '\n');
        idx += 5;
      }
      i += 1;
    }
  }
PLUS_4DIGITS_BREAK:

  // 10_000 .. 100_000
  for (i8 a = '1'; a <= '9'; ++a) {
    for (i8 b = 0; b < 100; ++b) {
      for (i8 c = 0; c < 100; ++c) {
        if (i >= 1000000 + 100000) {
          goto PLUS_5DIGITS_BREAK;
        }
        if (TABLE[i]) {
          ASSIGN(0, a);
          MEMCPY(1, b);
          MEMCPY(3, c);
          ASSIGN(5, '\n');
          idx += 6;
        }
        i += 1;
      }
    }
  }
PLUS_5DIGITS_BREAK:

  // 100_000 .. 1_000_000
  for (i8 a = 10; a < 100; ++a) {
    for (i8 b = 0; b < 100; ++b) {
      for (i8 c = 0; c < 100; ++c) {
        if (i >= 1000000 + 1000000) {
          goto PLUS_6DIGITS_BREAK;
        }
        if (TABLE[i]) {
          MEMCPY(0, a);
          MEMCPY(2, b);
          MEMCPY(4, c);
          ASSIGN(6, '\n');
          idx += 7;
        }
        i += 1;
      }
    }
  }
PLUS_6DIGITS_BREAK:

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
