from sys import stdin
from math import inf

COINS_COUNT, TARGET = map(int, stdin.readline().split())
COINS = [int(line) for line in stdin.read().split()]

# CACHE[x][y]: 동전 COINS[y:] 를 써서 x원을 만들 때 필요한 최소 동전 수.
# 불가능한 경우 inf 들어있음
CACHE = [[None]*(COINS_COUNT+1) for _ in range(TARGET+1)]

def solve_actual(current_target: int, begin_index: int) -> int:
    # current_target: [0, TARGET]
    # begin_index: [0, COINS_COUNT]
    #
    # returns:
    #   동전 COINS[begin_index:] 들을 써서 current_target원을 만들 때 필요한
    #   최소 동전 수. 불가능한 경우 inf 반환

    # 현재 쓸 수 있는 동전의 종류 수
    length = COINS_COUNT - begin_index
    # 현재 쓸 수 있는 동전들 가운데 맨 앞에 있는것
    current_coin = COINS[begin_index]

    # Handle base cases
    if current_target == 0:
        # 0 원은 0개의 동전으로 만들 수 있음
        return 0
    if length == 0:
        # 가진 동전이 없다면 무슨 수를 써도 양수의 금액을 만들 수 없음
        return inf
    if length == 1:
        # 나누어 떨어지는 경우에만 답이 나옴
        return current_target//current_coin if current_target % current_coin == 0 else inf

    return min(
        # current_coin을 i개 사용한 경우, 'current_target - i*current_coin' 원을
        # 남은 동전들로 만들어야 한다.
        i + solve(current_target - i * current_coin, begin_index + 1)
        for i in range(current_target//current_coin + 1)
    )

def solve(current_target: int, begin_index: int) -> int:
    # current_target: [0, TARGET]
    # begin_index: [0, COINS_COUNT]

    cache_entry = CACHE[current_target][begin_index]
    if cache_entry is not None:
        return cache_entry

    result = solve_actual(current_target, begin_index)
    CACHE[current_target][begin_index] = result
    return result

answer = solve(TARGET, 0)
if answer == inf:
    print('-1')
else:
    print(answer)
