N, M, B = map(int, input().split())
MAP = [
    [*map(int, input().split())] for _ in range(N)
]

def cost(desired_height: int):
    if desired_height > 256:
        # 너무 높음
        return float('inf')

    time_cost = 0
    block_cost = 0

    for row in range(N):
        for col in range(M):
            diff = MAP[row][col] - desired_height
            if diff > 0:
                # 원하는 높이보다 높음, 깎아야함: 2초 소요, 블록 획득
                time_cost += 2 * diff
                block_cost -= diff
            elif diff < 0:
                # 원하는 높이보다 낮음, 쌓아야함: 1초 소요, 블록 소모
                time_cost += (-diff)
                block_cost += (-diff)

    if block_cost > B:
        # 갖고있는 블록 수가 모자람, 불가능
        return float('inf')

    return time_cost


#
# 높이의 범위는 [0, 257), 이진탐색으로 가능한 가장 높은 높이 찾기
#
lo = 0
hi = 257

# Loop invariant:
#   lo < hi
#   cost(lo) < inf
#   cost(hi) == inf
while lo + 1 < hi:
    mid = (lo + hi)//2
    if cost(mid) == float('inf'):
        hi = mid
    else:
        lo = mid

upper_bound = hi


#
# 이진탐색으로 최소점 찾기
#
lo = 0
hi = upper_bound

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
