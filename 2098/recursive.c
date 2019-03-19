#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

static u8 COUNT;
static u32 COST[16][16];
static u16 ADJACENCIES[16];

const static u32 UINT31_MAX = (1u<<31u) - 1u;

typedef struct {
  bool cached : 1;
  u32 value : 31;
} CacheType;
_Static_assert(sizeof(CacheType) == sizeof(u32), "sizeof(CacheType) if not 4");
CacheType CACHE[16][1<<16];

// TSP(시작점, 들를 점들) = min(
//     '시작점 → x 비용' + TSP(x, 들를 점들 - x)
//     for x in '시작점과 인접한 점들'
// )
static u32 tsp_actual(u8, u16);
static u32 tsp(u8 start, u16 candidates) {
  if (CACHE[start][candidates].cached) {
    return CACHE[start][candidates].value;
  }

  const u32 value = tsp_actual(start, candidates);
  CACHE[start][candidates] = (CacheType){ .cached = true, .value = value };
  return value;
}

static u32 tsp_actual(u8 start, u16 candidates) {
  if (candidates == 0) {
    return COST[start][0];
  }

  const u16 adjacencies_of_start = candidates & ADJACENCIES[start];

  // 시작점에 인접한 점이 하나도 없는경우 여행이 불가능함
  if (adjacencies_of_start == 0) {
    return UINT31_MAX;
  }

  u16 bitset = adjacencies_of_start;
  u32 min = UINT31_MAX;
  for (u8 vertex = 0; bitset != 0; ++vertex, bitset >>= 1) {
    if ((bitset & 1) == 0) { continue; }

    const u32 cost = COST[start][vertex];
    if (cost == UINT31_MAX) { continue; }
    const u32 res = tsp(vertex, candidates & ~(1<<vertex));
    if (res == UINT31_MAX) { continue; }

    if (min > cost + res) {
      min = cost + res;
    }
  }
  return min;
}

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
      COST[row][col] = num == 0 ? UINT31_MAX : num;
    }
  }

  // ADJACENCIES 계산
  // ADJACENCIES[i] = 정점 i에서 출발해 도달할 수 있는 인접한 점들, bitset
  for (u8 i = 0; i < COUNT; ++i) {
    u16 sum = 0;
    for (u8 j = 0; j < COUNT; ++j) {
      if (COST[i][j] == UINT31_MAX) { continue; }

      sum |= 1<<j;
    }
    ADJACENCIES[i] = sum;
  }

  printf("%d\n", tsp(0, (1<<COUNT) - 2));
}
