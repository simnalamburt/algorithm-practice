// gcc solution.c -Wall -Wextra -Wpedantic -Werror -std=c18
//
// Reference:
//   https://www.acmicpc.net/problem/5639

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Linux specific headers
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

typedef uint8_t u8;
typedef uint32_t u32;

struct Node { u32 value, left, right; };
static struct Node TREE[10000];

void dfs(u32 index) {
  const struct Node node = TREE[index];

  if (node.left != 0) { dfs(node.left); }
  if (node.right != 0) { dfs(node.right); }
  printf("%d\n", node.value);
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
      TREE[index++].value = number_wip;
      number_wip = 0;
      is_wip = false;
    }
  }
  const size_t len = index;

  //
  // 트리 초기화
  //
  for (size_t idx = 1; idx < len; ++idx) {
    // TREE[0..idx] 까지 트리가 초기화된 상태이고
    // TREE[idx] 를 트리에 삽입하면 됨

    size_t i = 0;
    while (true) {
      u32 * const next = TREE[idx].value < TREE[i].value ?
        &TREE[i].left : &TREE[i].right;
      if (*next == 0) {
        *next = idx;
        // Return
        break;
      }

      // Tail recursion
      i = *next;
    }

  }

  //
  // 트리 순회
  //
  dfs(0);
}
