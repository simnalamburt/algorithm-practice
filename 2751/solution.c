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
typedef size_t usize;

static i32 parse(const u8 *addr, off_t file_size, off_t *index) {
  bool is_plus = true;
  i32 number = 0;

  if (addr[*index] == '-') {
    is_plus = false;
    *index += 1;
  }

  for (; *index < file_size; ++*index) {
    const u8 ch = addr[*index];
    const bool is_num = '0' <= ch && ch <= '9';
    if (!is_num) { break; }
    number = 10*number + ch - '0';
  }

  *index += 1;
  return is_plus ? number : -number;
}

static const u8 ITOA_LUT[] =
  "00010203040506070809"
  "10111213141516171819"
  "20212223242526272829"
  "30313233343536373839"
  "40414243444546474849"
  "50515253545556575859"
  "60616263646566676869"
  "70717273747576777879"
  "80818283848586878889"
  "90919293949596979899";

// LUT, mod by 100. -1000000 <= val <= 1000000 일때에만 정상적으로 동작함.
//
// Reference: https://github.com/miloyip/itoa-benchmark
//
// NOTE: 카운팅소트만 아니었다면 10진법 대신 16진법을 써서 성능을 미세하게 올릴 수 있다.
static u8 itoa(u8 buffer[8], i32 val) {
  if (val < 0) {
    const usize ret = itoa(buffer, -val);
    buffer[ret - 1] = '-';
    return ret - 1;
  }

  u8 p = 8;
  while (val >= 100) {
    const i32 old = val;

    p -= 2;
    val /= 100;
    const usize idx = (old - (val*100))*2;
    buffer[p] = ITOA_LUT[idx];
    buffer[p + 1] = ITOA_LUT[idx + 1];
  }

  p -= 2;
  buffer[p] = ITOA_LUT[2*val];
  buffer[p + 1] = ITOA_LUT[2*val + 1];

  return p + (val < 10);
}

static bool TABLE[2000001];

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
  for (i32 i = 0; i < count; ++i) {
    const i32 num = parse(addr, file_size, &index);
    TABLE[num + 1000000] = 1;
  }

  // 출력
  setvbuf(stdout, NULL, _IOFBF, 1024 * 1024);

  u8 buffer[9];
  buffer[8] = '\n';
  for (i32 i = 0; i < 2000001; ++i) {
    if (!TABLE[i]) { continue; }
    u8 offset = itoa(buffer, i - 1000000);
    fwrite(buffer + offset, 1, 9 - offset, stdout);
  }
  fflush(stdout);
  _exit(0);
}
