K, N = map(int, input().split())
cables = [int(input()) for _ in range(K)]

def calc(length: int) -> int:
    return sum(cable // length for cable in cables)

trial = 0

# calc 함수는 단조감소함수임을 쉽게 알 수 있다. 그리고 calc(1)은 무조건 N보다
# 크고, calc(sum(cables)//N + 1)은 무조건 N보다 작으므로, 중간값 정리에 의해
# [1, sum(cables)//N] 구간에 해가 존재한다. 그 해는 이진탐색으로 찾으면 된다.
#
# Loop invariant:
#   sum(cable // lo for cable in cables) >= N
#   sum(cable // hi for cable in cables) < N
#   lo < hi
lo = 1
hi = sum(cables)//N + 1
while lo + 1 < hi:
    mid = (lo + hi)//2
    n = calc(mid)

    trial += 1
    print(f'({lo=} {hi=}) {mid=} {n=}')

    if n >= N:
        lo = mid
    else:
        hi = mid

print(f'{lo=} {trial=}')
