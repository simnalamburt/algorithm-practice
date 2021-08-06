HEIGHTS = [0]*257

N, M, B = map(int, input().split())
for _ in range(N):
    for word in input().split():
        height = int(word)
        HEIGHTS[height] += 1

def cost(desired_height: int):
    if desired_height > 256:
        # instead of inf, use ordered number
        return 2100000000 + desired_height

    time_cost = 0
    block_cost = 0
    for height, count in enumerate(HEIGHTS):
        diff = height - desired_height
        time_cost += (2 if diff > 0 else -1) * diff * count
        block_cost -= diff * count

    if block_cost > B:
        # 갖고있는 블록 수가 모자람, 불가능
        return 2100000000 + desired_height

    return time_cost


#
# 이진탐색으로 최소점 찾기
#
lo = 0
hi = 257

# cost(0..257)은 강한단조감소수열 + 여러개의 최소점 + 강한단조증가수열 임을 알
# 수 있다.

# Loop invariant:
#   lo < hi:
#   lo 는 강한단조감소수열 + 여러개의 최소점 에 포함됨
#   hi 는 여러개의 최소점 + 강한단조증가수열 에 포함됨
while lo + 1 < hi:
    mid = (lo + hi)//2
    if cost(mid - 1) >= cost(mid):
        # 강한단조감소 or 여러개의 최소점
        lo = mid
    else:
        # 강한단조증가
        hi = mid

min_height = lo
min_cost = cost(min_height)

print(min_cost, min_height)
