from collections.abc import Iterator
from heapq import heappush, heappop

def neighbors(current: int, upper_bound: int) -> Iterator[int]:
    i = 1
    while (neighbor := current + i**2) <= upper_bound:
        yield neighbor
        i += 1

n = int(input())

# Dijkstra's algorithm
DIST = [float('inf')]*(n+1)
DIST[0] = 0
Q = [(0, 0)]
while Q:
    dist, idx = heappop(Q)

    if DIST[idx] < dist:
        continue

    if idx == n:
        break

    for neighbor in neighbors(idx, n):
        new_dist = dist + 1
        if DIST[neighbor] <= new_dist:
            continue

        DIST[neighbor] = new_dist
        heappush(Q, (new_dist, neighbor))

answer = DIST[n]
print(answer)
