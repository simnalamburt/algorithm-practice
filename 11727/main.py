def solve(n: int) -> int:
    if n == 0:
        return 1
    if n == 1:
        return 1
    # Invariant: n >= 2
    DP = [0]*(n + 1)
    DP[0] = 1
    DP[1] = 1
    for i in range(2, n + 1):
        DP[i] = DP[i - 1] + DP[i - 2]*2
    return DP[n] % 10007

n = int(input())
print(solve(n))
