# W: 가로, H: 세로
W, H = map(int, input().split())
MAP = [[*map(int, input().split())] for _ in range(H)]

tasks = [
    (r, c, 1)
    for r in range(H)
    for c in range(W)
    if MAP[r][c] == 1
]

while tasks:
    r, c, n = tasks.pop(0)
    if n != 1 and MAP[r][c] != 0:
        continue
    MAP[r][c] = n
    if r > 0:
        tasks.append((r - 1, c, n + 1))
    if r < H - 1:
        tasks.append((r + 1, c, n + 1))
    if c > 0:
        tasks.append((r, c - 1, n + 1))
    if c < W - 1:
        tasks.append((r, c + 1, n + 1))

all_non_zero = all(all(c != 0 for c in row) for row in MAP)
if all_non_zero:
    print(max(max(row) for row in MAP) - 1)
else:
    print(-1)

# NOTE:
#   이상한짓 하지말고 얌전히 BFS를 짜자
#   버그있었음
