K, N = map(int, input().split())
cables = [int(input()) for _ in range(K)]

# Loop invariant:
#   sum(cable // lo for cable in cables) >= N
#   sum(cable // hi for cable in cables) < N
#   lo < hi
lo = 1
hi = sum(cables)//N + 1
while lo + 1 < hi:
    mid = (lo + hi)//2
    n = sum(cable // mid for cable in cables)

    if n >= N:
        lo = mid
    else:
        hi = mid

print(lo)
