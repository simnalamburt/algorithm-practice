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
typedef uint64_t u64;

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

static const u16 ITOA_LUT[100] = {
  0x3030, 0x3130, 0x3230, 0x3330, 0x3430, 0x3530, 0x3630, 0x3730, 0x3830, 0x3930,
  0x3031, 0x3131, 0x3231, 0x3331, 0x3431, 0x3531, 0x3631, 0x3731, 0x3831, 0x3931,
  0x3032, 0x3132, 0x3232, 0x3332, 0x3432, 0x3532, 0x3632, 0x3732, 0x3832, 0x3932,
  0x3033, 0x3133, 0x3233, 0x3333, 0x3433, 0x3533, 0x3633, 0x3733, 0x3833, 0x3933,
  0x3034, 0x3134, 0x3234, 0x3334, 0x3434, 0x3534, 0x3634, 0x3734, 0x3834, 0x3934,
  0x3035, 0x3135, 0x3235, 0x3335, 0x3435, 0x3535, 0x3635, 0x3735, 0x3835, 0x3935,
  0x3036, 0x3136, 0x3236, 0x3336, 0x3436, 0x3536, 0x3636, 0x3736, 0x3836, 0x3936,
  0x3037, 0x3137, 0x3237, 0x3337, 0x3437, 0x3537, 0x3637, 0x3737, 0x3837, 0x3937,
  0x3038, 0x3138, 0x3238, 0x3338, 0x3438, 0x3538, 0x3638, 0x3738, 0x3838, 0x3938,
  0x3039, 0x3139, 0x3239, 0x3339, 0x3439, 0x3539, 0x3639, 0x3739, 0x3839, 0x3939,
};

// LUT, mod by 100. -1000000 <= val <= 1000000 일때에만 정상적으로 동작함.
//
// Reference: https://github.com/miloyip/itoa-benchmark
//
// NOTE: 카운팅소트만 아니었다면 10진법 대신 16진법을 써서 성능을 미세하게 올릴 수 있다.
static u8 itoa(u8 buffer[8], i32 val) {
  if (val < 0) {
    const u8 ret = itoa(buffer, -val);
    buffer[ret - 1] = '-';
    return ret - 1;
  }

  u8 p = 8;
  while (val >= 100) {
    const i32 old = val;

    p -= 2;
    val /= 100;
    memcpy(&buffer[p], &ITOA_LUT[old - (val*100)], 2);
  }

  p -= 2;
  memcpy(&buffer[p], &ITOA_LUT[val], 2);

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
    TABLE[num + 1000000] = 1;
  }

  // 출력할 내용을 mmap에 기록
  u64 idx = 0;
  u8 buffer[8];
  for (i32 i = 0; i < 2000001; ++i) {
    if (!TABLE[i]) { continue; }

    const u8 offset = itoa(buffer, i - 1000000);
    const u8 len = 8 - offset;
    memcpy(&OUTPUT_BUFFER[idx], buffer + offset, len);
    idx += len;

    OUTPUT_BUFFER[idx] = '\n';
    idx += 1;
  }

  // 출력
  write(STDOUT_FILENO, OUTPUT_BUFFER, idx);
  _exit(0);
}
