N = int(input())
MAP = [[*map(int, input().split())] for _ in range(N)]

DP = [[1]*N for _ in range(N)]

k = 1
while k < N:
    for i in range(0, N, k*2):
        for j in range(0, N, k*2):
            if (
                DP[i][j] == DP[i+k][j] == DP[i][j+k] == DP[i+k][j+k] == 1 and
                MAP[i][j] == MAP[i+k][j] == MAP[i][j+k] == MAP[i+k][j+k]
            ):
                # Nothing to do
                ...
            else:
                DP[i][j] = DP[i][j] + DP[i+k][j] + DP[i][j+k] + DP[i+k][j+k]
    k *= 2

print(DP[0][0])

# NOTE: 입출력 스펙 똑바로 안읽었음
