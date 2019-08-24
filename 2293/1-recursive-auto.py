from sys import stdin
from functools import lru_cache

COINS_COUNT, TARGET = map(int, stdin.readline().split())
COINS = sorted(map(int, stdin.read().split()), reverse=True)

@lru_cache()
def solve(target: int, begin_index: int) -> int:
    length = COINS_COUNT - begin_index
    current_coin = COINS[begin_index]

    # Handle base cases
    if target == 0:
        return 1
    if length == 0:
        return 0
    if length == 1:
        return 1 if target % current_coin == 0 else 0

    return sum(
        solve(target - i * current_coin, begin_index + 1)
        for i in range(target//current_coin + 1)
    )

answer = solve(TARGET, 0)
print(answer)
