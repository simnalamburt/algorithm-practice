#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

static u8 COUNT;
static u32 COST[16][16];
static u16 ADJACENCIES[16];
static u32 CACHE[16][1<<16];

int main() {
  // COUNT 입력받음. [2, 16] 범위 밖일경우 즉시 프로그램 종료
  scanf("%"SCNu8, &COUNT);
  if (COUNT < 2 || 16 < COUNT) {
    fprintf(stderr, "정점의 수는 2 이상 16 이하여야 합니다.\n");
    return -1;
  }

  // COST 입력받음
  // COST[i][j] = 정점 i에서 j로 가는데에 드는 비용. 갈 수 없을경우 ∞
  for (u8 row = 0; row < COUNT; ++row) {
    for (u8 col = 0; col < COUNT; ++col) {
      u32 num;
      scanf("%"SCNu32, &num);
      COST[row][col] = num == 0 ? UINT32_MAX : num;
    }
  }

  // ADJACENCIES 계산
  // ADJACENCIES[i] = 정점 i에서 출발해 도달할 수 있는 인접한 점들, bitset
  for (u8 i = 0; i < COUNT; ++i) {
    u16 sum = 0;
    for (u8 j = 0; j < COUNT; ++j) {
      if (COST[i][j] == UINT32_MAX) { continue; }

      sum |= 1<<j;
    }
    ADJACENCIES[i] = sum;
  }

  // DP 수행
  // TSP(시작점, 들를 점들) = min(
  //     '시작점 → x 비용' + TSP(x, 들를 점들 - x)
  //     for x in '시작점과 인접한 점들'
  // )
  for (u8 start = 0; start < COUNT; ++start) {
    CACHE[start][0] = COST[start][0];
  }
  for (u16 candidates = 1; candidates < (1<<COUNT) - 1; ++candidates) {
    for (u8 start = 0; start < COUNT; ++start) {
      // candidates 안에 start가 있는경우는 불가능함. 패스
      if (((1<<start) & candidates) != 0) {
        continue;
      }

      const u16 adjacencies_of_start = candidates & ADJACENCIES[start];

      // 시작점에 인접한 점이 하나도 없는경우 여행이 불가능함
      if (adjacencies_of_start == 0) {
        CACHE[start][candidates] = UINT32_MAX;
        continue;
      }

      u16 bitset = adjacencies_of_start;
      u32 min = UINT32_MAX;
      for (u8 vertex = 0; bitset != 0; ++vertex, bitset >>= 1) {
        if ((bitset & 1) == 0) { continue; }

        const u32 cost = COST[start][vertex];
        if (cost == UINT32_MAX) { continue; }
        const u32 cache = CACHE[vertex][candidates & ~(1<<vertex)];
        if (cache == UINT32_MAX) { continue; }

        if (min > cost + cache) {
          min = cost + cache;
        }
      }
      CACHE[start][candidates] = min;
    }
  }

  printf("%d\n", CACHE[0][(1<<COUNT) - 2]);
}
