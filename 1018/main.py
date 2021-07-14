N, M = map(int, input().split())
board = [input() for _ in range(N)]

def each(a, b):
    w = sum(
        1 if board[i][j] != ('W' if (i + j) % 2 == 0 else 'B') else 0
        for i in range(a, a + 8)
        for j in range(b, b + 8)
    )
    return min(w, 64-w)

print(min(
    each(a, b)
    for a in range(0, N-7)
    for b in range(0, M-7)
))
