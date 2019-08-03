#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

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

  // TODO
  for (unsigned long long iter = 0;; ++iter) {
    const bool debug = false; // 1708 <= iter && iter <= 1709;
    // TODO
    if (debug) {
      unsigned long long sum = 0;
      for (u16 i = 0; i < width*height; ++i) { sum += costs[i]; }
      printf("iter = %llu\n", iter);
      printf("sum(costs) = %llu\n", sum);
      printf("len(deque) = %"PRIu16"\n", deque_end);
      printf("deque[:5] = [");
      for (u16 i = 0; i < 4; ++i) {
        printf("(%d, %d), ", deque[i].x, deque[i].y);
      }
      printf("(%d, %d)]\n", deque[5].x, deque[5].y);
      printf("deque[-5:] = [");
      for (u16 i = deque_end - 5; i < deque_end - 1; ++i) {
        printf("(%d, %d), ", deque[i].x, deque[i].y);
      }
      printf("(%d, %d)]\n", deque[deque_end - 1].x, deque[deque_end - 1].y);
    }

    assert(0 < deque_end);
    assert(deque_end < width*height - 1);

    const tuple pos = deque[--deque_end];

    assert(0 <= pos.x);
    assert(0 <= pos.y);
    assert(pos.x < width);
    assert(pos.y < height);

    // 도착함
    if (pos.x == width - 1 && pos.y == height - 1) {
      break;
    }

    assert(pos.y*width + pos.x < width*height);
    const u16 cost = costs[pos.y*width + pos.x];

    // 인접한 점들 순회
    const tuple adjacencies[4] = {
      (tuple) { pos.x, pos.y - 1 },
      (tuple) { pos.x - 1, pos.y },
      (tuple) { pos.x + 1, pos.y },
      (tuple) { pos.x, pos.y + 1 },
    };
    for (u8 i = 0; i < 4; ++i) {
      const u8 x = adjacencies[i].x;
      const u8 y = adjacencies[i].y;
      if (x >= width || y >= height) { continue; }
      assert(0 <= x);
      assert(0 <= y);
      assert(x < width);
      assert(y < height);

      assert(y*(width + 1) + x < height*(width+1));
      assert(
        world[y*(width + 1) + x] == '0' ||
        world[y*(width + 1) + x] == '1'
      );
      const bool is_wall = world[y*(width + 1) + x] == '1';
      const u16 new_cost = cost + is_wall;
      assert(y*width + x < width*height);
      if (costs[y*width + x] <= new_cost) { continue; }

      costs[y*width + x] = new_cost;

      // 코스트가 무조건 0 아니면 1이어서 이렇게 해도 됨
      if (is_wall) {
        if (debug) { printf("Push Start (%hhu, %hhu)\n", x, y); } // TODO
        // deque 맨 앞에 원소 삽입
        if (debug) { printf("(ㅇㅅㅇ\n"); } // TODO
        for (u16 i = deque_end + 1; i > 0; --i) {
          if (debug) { printf("ㅇㅅㅇ\n"); } // TODO
          deque[i] = deque[i - 1];
        }
        if (debug) { printf("ㅇㅅㅇ)\n"); } // TODO
        deque[0] = (tuple) { x, y };
        deque_end += 1;
      } else {
        if (debug) { printf("Push End (%hhu, %hhu)\n", x, y); } // TODO
        deque[deque_end++] = (tuple) { x, y };
      }
    }
    if (debug) { putchar('\n'); } // TODO
  }

  printf("%"PRIu16"\n", costs[height*width - 1]);
}
// TODO: assert 제거
