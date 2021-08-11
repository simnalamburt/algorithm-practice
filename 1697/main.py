from heapq import heappush, heappop

N, K = map(int, input().split())

# Dijkstra's algorithm
DIST = [float('inf')] * 100_001
DIST[N] = 0
Q = [(0, N)]
while Q:
    dist, pos = heappop(Q)

    if DIST[pos] < dist:
        continue

    if pos == K:
        break

    for neighbor in [pos - 1, pos + 1, 2*pos]:
        if not (0 <= neighbor < 100_001):
            continue

        new_dist = dist + 1
        if DIST[neighbor] <= new_dist:
            continue

        DIST[neighbor] = new_dist
        heappush(Q, (new_dist, neighbor))

answer = DIST[K]

print(answer)
