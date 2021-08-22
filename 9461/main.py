DP = [1, 1, 1, 2, 2] + [0] * 95
for i in range(5, 100):
    DP[i] = DP[i-5] + DP[i-1]

T = int(input())
for _ in range(T):
    N = int(input())
    print(DP[N-1])
