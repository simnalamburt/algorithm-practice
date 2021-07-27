N = int(input())

SUM = 0
CTR = [0]*8001
MIN = 4000
MAX = -4000

for _ in range(N):
    n = int(input())

    SUM += n
    CTR[n+4000] += 1
    if n < MIN:
        MIN = n
    elif MAX < n:
        MAX = n

mean = round(SUM/N)

remain = N//2
for i, count in enumerate(CTR):
    remain -= count
    if remain < 0:
        median = i - 4000
        break

mode = max(range(8001), key=lambda n:CTR[n]) - 4000
RANGE = MAX - MIN

print(mean)
print(median)
print(mode)
print(RANGE)
