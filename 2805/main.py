N, M = map(int, input().split())
trees = [*map(int, input().split())]

lo = 0
hi = max(trees)

# Loop invariant:
#   lo < hi
#   f(trees, lo) >= M
#   f(trees, hi) < M
while lo + 1 < hi:
    mid = (lo + hi)//2
    val = sum(tree - mid for tree in trees if tree > mid)
    if val >= M:
        lo = mid
    else:
        hi = mid

print(lo)
