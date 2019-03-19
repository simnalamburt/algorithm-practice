from math import inf
from functools import lru_cache

# 정점의 수
COUNT = int(input())

# COST[i][j] = 정점 i에서 j로 가는데에 드는 비용. 갈 수 없을경우 ∞
COST = [
    [
        int(x) if x != '0' else inf
        for x in input().split()
    ]
    for _ in range(COUNT)
]

# ADJACENCIES[i] = 정점 i에서 출발해 도달할 수 있는 인접한 점들, bitset
ADJACENCIES = [
    sum(1<<j for j in range(COUNT) if COST[i][j] < inf)
    for i in range(COUNT)
]

def iterate(bitset):
    i = 0
    while bitset != 0:
        if bitset & 1 == 1:
            yield i
        bitset >>= 1
        i += 1

# DP 계산 결과 저장하는곳
CACHE = [(1<<COUNT)*[0] for _ in range(COUNT)]

# TSP(시작점, 들를 점들) = min(
#     '시작점 → x 비용' + TSP(x, 들를 점들 - x)
#     for x in '시작점과 인접한 점들'
# )
for start in range(COUNT):
    CACHE[start][0] = COST[start][0]
for candidates in range(1, (1<<COUNT) - 1):
    for start in range(COUNT):
        # 불가능한 경우 패스
        if (1<<start) & candidates != 0:
            continue

        adjacencies_of_start = candidates & ADJACENCIES[start]
        CACHE[start][candidates] = (
            min(
                COST[start][vertex] + CACHE[vertex][candidates & ~(1<<vertex)]
                for vertex in iterate(adjacencies_of_start)
            )
            if adjacencies_of_start > 0 else
            # 시작점에 인접한 점이 하나도 없는경우 여행이 불가능함
            inf
        )

print(CACHE[0][(1<<COUNT) - 2])
