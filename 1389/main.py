from heapq import heappush, heappop

N, M = map(int, input().split())

DIST = [[float('inf')]*N for _ in range(N)]

for i in range(N):
    DIST[i][i] = 0

for _ in range(M):
    a, b = map(int, input().split())
    DIST[a - 1][b - 1] = DIST[b - 1][a - 1] = 1

# Floyd–Warshall
for m in range(N):
    for s in range(N):
        for e in range(N):
            d = DIST[s][m] + DIST[m][e]
            if DIST[s][e] > d:
                DIST[s][e] = d

idx = min(range(N), key=lambda i: sum(DIST[i]))
print(idx + 1)
