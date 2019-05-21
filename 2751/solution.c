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

typedef int32_t i32;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

// 틀린 입력이 절대 들어오지 않고 입력이 스펙대로만 들어온다고 가정하면 더 빠른
// atoi를 만들 수 있다.
static i32 parse(const u8 *addr, off_t len, off_t *index) {
  bool is_plus = true;
  i32 number = 0;

  // NOTE: 입력이 스펙대로만 들어온다면 self.addr[self.index]에 접근하기 전에
  // 바운더리 체크를 먼저 할 필요가 없음

  if (addr[*index] == '-') {
    is_plus = false;
    *index += 1;
  }

  while (*index < len) {
    const u8 ch = addr[*index];
    if (ch < '0' || '9' < ch) { break; }
    number = 10*number + ch - '0';
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

// LUT, mod by 100. 0 <= val <= 1000000 일때에만 정상적으로 동작함.
//
// Reference: https://github.com/miloyip/itoa-benchmark
//
// NOTE: 카운팅소트만 아니었다면 10진법 대신 16진법을 써서 성능을 미세하게 올릴 수 있다.
static u8 itoa(u8 buffer[8], u32 val) {
  u8 p = 8;
  while (val >= 100) {
    p -= 2;
    const i32 rem = val % 100;
    val /= 100;
    memcpy(&buffer[p], &ITOA_LUT[rem*2], 2);
  }
  p -= 2;
  memcpy(&buffer[p], &ITOA_LUT[val*2], 2);

  return p + (val < 10);
}

static bool TABLE[2000001];

// /dev/stdin 에 쓰면 불필요하게 IO로 시간 쓸까봐 .bss 에 메모리 만듬
static u8 OUTPUT_BUFFER[7888904];

int main() {
  // stdin 길이 측정
  struct stat stat;
  const int ret = fstat(STDIN_FILENO, &stat);
  if (ret != 0) { return -1; }
  const off_t file_size = stat.st_size;

  // stdin mmap 수행
  u8 * const input = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, STDIN_FILENO, 0);
  if (input == MAP_FAILED) { return -1; }

  // 오토마타로 stdin 파싱
  off_t index = 0;
  const i32 count = parse(input, file_size, &index);
  for (i32 i = 0; i < count; ++i) {
    const i32 num = parse(input, file_size, &index);
    // -1_000_000 <= num <= 1_000_000
    TABLE[num + 1000000] = 1;
  }

  // 출력할 내용을 OUTPUT_BUFFER에 기록
  u32 idx = 0;
  u8 buffer[8];
  for (u32 i = 0; i < 1000000; ++i) {
    if (!TABLE[i]) { continue; }

    OUTPUT_BUFFER[idx] = '-';
    idx += 1;

    const u32 num = 1000000 - i;

    const u8 offset = itoa(buffer, num);
    const u8 len = 8 - offset;
    memcpy(&OUTPUT_BUFFER[idx], &buffer[offset], len);
    idx += len;
    OUTPUT_BUFFER[idx] = '\n';
    idx += 1;
  }
  for (u32 i = 1000000; i < 2000001; ++i) {
    if (!TABLE[i]) { continue; }

    const u32 num = i - 1000000;

    const u8 offset = itoa(buffer, num);
    const u8 len = 8 - offset;
    memcpy(&OUTPUT_BUFFER[idx], &buffer[offset], len);
    idx += len;
    OUTPUT_BUFFER[idx] = '\n';
    idx += 1;
  }

  // 출력
  write(STDOUT_FILENO, OUTPUT_BUFFER, idx);
  _exit(0);
}
