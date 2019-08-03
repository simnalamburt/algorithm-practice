#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>

// Linux specific headers
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

typedef int8_t i8;
typedef uint8_t u8;
typedef uint16_t u16;
typedef struct { u8 x, y; } tuple;

// 틀린 입력이 절대 들어오지 않고 입력이 스펙대로만 들어온다고 가정하면 더 빠른
// atoi를 만들 수 있다.
static inline u8 parse(const u8 *addr, off_t *p_index) {
  off_t idx = *p_index;

  u8 i = 0, number = 0;
#pragma unroll 3
  for (; i < 3; ++i) {
    const i8 ch = addr[idx + i] - '0';
    // NOTE: 올바른 입력만 들어온다면, '0'보다 작은 글자는 무조건 '\n', ' ' 이다
    if (ch < 0) { break; }
    number = 10*number + ch;
  }
  *p_index = idx + i + 1;
  return number;
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
  u8 * const input = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
  if (input == MAP_FAILED) { return -1; }

  //
  // 오토마타로 stdin 파싱
  //
  off_t index = 0;
  const u16 width = parse(input, &index);
  const u16 height = parse(input, &index);
  const u8 * const world = input + index; // world[y*(width + 1) + x]

  //
  // Dijkstra
  //
  u16 costs[width*height]; // costs[y*width + x]
  memset(costs, 0xFF, sizeof costs);
  costs[0] = 0;

  tuple deque[width*height];
  deque[0] = (tuple) { 0, 0 };
  u16 deque_end = 1;

  for (;;) {
    const tuple pos = deque[--deque_end];

    // 도착함
    if (pos.x == width - 1 && pos.y == height - 1) {
      break;
    }

    const u16 cost = costs[pos.y*width + pos.x];

    // 인접한 점들 순회
    const tuple adjacencies[] = {
      (tuple) { pos.x, pos.y - 1 },
      (tuple) { pos.x - 1, pos.y },
      (tuple) { pos.x + 1, pos.y },
      (tuple) { pos.x, pos.y + 1 },
    };
    for (u8 i = 0; i < 4; ++i) {
      const u8 x = adjacencies[i].x;
      const u8 y = adjacencies[i].y;
      if (x >= width || y >= height) { continue; }

      const u8 is_wall = world[y*(width + 1) + x] == '1';
      const u16 new_cost = cost + is_wall;
      if (costs[y*width + x] <= new_cost) { continue; }

      costs[y*width + x] = new_cost;

      // 코스트가 무조건 0 아니면 1이어서 이렇게 해도 됨
      if (is_wall) {
        // deque 맨 앞에 원소 삽입
        for (u8 i = deque_end + 1; i > 0; --i) {
          deque[i] = deque[i - 1];
        }
        deque[0] = (tuple) { x, y };
        deque_end += 1;
      } else {
        deque[deque_end++] = (tuple) { x, y };
      }
    }
  }

  printf("%"PRIu16"\n", costs[height*width - 1]);
}
