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

# TSP(시작점, 들를 점들) = min(
#     '시작점 → x 비용' + TSP(x, 들를 점들 - x)
#     for x in '시작점과 인접한 점들'
# )
@lru_cache(None)
def tsp(start, candidates, dest):
    # 들를 점이 하나도 없는 경우 바로 계산이 끝남
    if candidates == 0:
        return COST[start][dest]

    adjacencies_of_start = candidates & ADJACENCIES[start]

    # 시작점에 인접한 점이 하나도 없는경우 여행이 불가능함
    if adjacencies_of_start == 0:
        return inf

    return min(
        COST[start][vertex] + tsp(vertex, candidates & ~(1<<vertex), dest)
        for vertex in iterate(adjacencies_of_start)
    )

print(tsp(0, (1<<COUNT) - 2, 0))
