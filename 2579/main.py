def solve(stairs: list[int]) -> int:
    if len(stairs) == 0:
        return 0
    if len(stairs) == 1:
        return stairs[0]
    if len(stairs) == 2:
        return stairs[0] + stairs[1]
    # Invariant: len(stairs) >= 3

    # DP[i] : stairs[:i] 에서의 부분해
    DP = [-1]*(N + 1)

    DP[0] = 0
    DP[1] = stairs[0]
    DP[2] = stairs[0] + stairs[1]

    for i in range(3, len(stairs) + 1):
        DP[i] = max(
            DP[i-2] + stairs[i-1],
            DP[i-3] + stairs[i-2] + stairs[i-1],
        )
    return DP[-1]

N = int(input())
stairs = [int(input()) for _ in range(N)]
print(solve(stairs))
