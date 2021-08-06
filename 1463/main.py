N = int(input())
DP = [None] + [0]*N
for i in range(2, N + 1):
    candidate = [DP[i-1] + 1]
    if i % 3 == 0:
        candidate.append(DP[i//3] + 1)
    if i % 2 == 0:
        candidate.append(DP[i//2] + 1)
    DP[i] = min(candidate)
print(DP[N])
