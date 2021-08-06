N = int(input())
MAP = [[*map(int, input().split())] for _ in range(N)] # 0: white, 1: blue

def solve(i: int, j: int, n: int) -> tuple[int, int]:
    # Invariant:
    #   n is power of 2
    #   i % n == 0
    #   j % n == 0
    #
    # Returns: (# of white, # of blue)
    if n == 1:
        return (1, 0) if MAP[i][j] == 0 else (0, 1)

    k = n//2
    a = solve(i,     j,     k)
    b = solve(i + k, j,     k)
    c = solve(i,     j + k, k)
    d = solve(i + k, j + k, k)
    if a == b == c == d and (a == (1, 0) or a == (0, 1)):
        return a

    return (a[0] + b[0] + c[0] + d[0], a[1] + b[1] + c[1] + d[1])

answer = solve(0, 0, N)
print(answer[0])
print(answer[1])

# NOTE: 입출력 스펙 똑바로 안읽었음, join 하기 전에 str로 안만들었음
