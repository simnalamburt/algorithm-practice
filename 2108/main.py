N = int(input())

SUM = 0
CTR = [0]*8001
MIN = 4001
MAX = -4001

for _ in range(N):
    n = int(input())

    SUM += n
    CTR[n+4000] += 1
    if n < MIN:
        MIN = n
    if MAX < n:
        MAX = n

mean = round(SUM/N)

remain = N//2
for i, count in enumerate(CTR):
    remain -= count
    if remain < 0:
        median = i - 4000
        break

freq = max(CTR)
modes = sorted(i - 4000 for i in range(8001) if CTR[i] == freq)
mode = modes[1] if len(modes) > 1 else modes[0]
RANGE = MAX - MIN

print(mean)
print(median)
print(mode)
print(RANGE)
