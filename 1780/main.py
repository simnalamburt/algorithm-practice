N = int(input())
PAPER = [[*map(int, input().split())] for _ in range(N)]

def solve(n: int, row: int, col: int) -> tuple[int, int, int]:
    if n == 1:
        kind = PAPER[row][col]
        if kind == -1:
            return (1, 0, 0)
        elif kind == 0:
            return (0, 1, 0)
        else: # kind == 2
            return (0, 0, 1)

    m = n // 3
    partialSolutions = [
        solve(m, row + i*m, col + j*m)
        for i in range(3)
        for j in range(3)
    ]

    uniq = set(partialSolutions)
    if uniq == {(1, 0, 0)}:
        return (1, 0, 0)
    elif uniq == {(0, 1, 0)}:
        return (0, 1, 0)
    elif uniq == {(0, 0, 1)}:
        return (0, 0, 1)

    sumA, sumB, sumC = 0, 0, 0
    for A, B, C in partialSolutions:
        sumA += A
        sumB += B
        sumC += C

    return (sumA, sumB, sumC)

A, B, C = solve(N, 0, 0)
print(A)
print(B)
print(C)
