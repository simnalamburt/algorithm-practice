// gcc solution.c -Wall -Wextra -Wpedantic -Werror -std=c99
//
// Reference:
//   https://www.acmicpc.net/problem/5639

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

// Linux specific headers
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;

static u32 INPUTS[10001];

static u16 solve(u16 idx, u32 upper_bound) {
  const u32 pivot = INPUTS[idx];
  // pivot이 upper_bound 보다 크다 = 이 트리는 Nil이다
  if (upper_bound < pivot) {
    return idx;
  }

  // 왼쪽 서브트리가 끝나는 인덱스 == 오른쪽 서브트리 시작지점 인덱스
  const u16 idx_right = solve(idx + 1, pivot);
  // 오른쪽 서브트리가 끝나는 인덱스
  const u16 idx_end = solve(idx_right, upper_bound);

  // 방문
  printf("%" PRIu32 "\n", pivot);

  // 트리가 끝난 지점 리턴
  return idx_end;
}

int main() {
  // stdin 길이 측정
  struct stat stat;
  const int ret = fstat(STDIN_FILENO, &stat);
  if (ret != 0) { return -1; }
  const off_t file_size = stat.st_size;

  // stdin mmap 수행
  const u8 * const addr = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
  if (addr == MAP_FAILED) { return -1; }

  //
  // 오토마타로 stdin 파싱
  //
  bool is_wip = false;
  u32 number_wip = 0;
  size_t index = 0;
  for (off_t i = 0; i < file_size; ++i) {
    const u8 ch = addr[i];
    const bool is_num = '0' <= ch && ch <= '9';

    if (is_num) {
      number_wip = 10*number_wip + ch - '0';
      is_wip = true;
      continue;
    }

    if (is_wip) {
      // 숫자 파싱함
      INPUTS[index++] = number_wip;
      number_wip = 0;
      is_wip = false;
    }
  }
  const size_t len = index;

  //
  // 알고리즘 수행
  //
  INPUTS[len] = UINT32_MAX;
  solve(0, 1000000);
}
