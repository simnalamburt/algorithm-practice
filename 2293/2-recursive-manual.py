from sys import stdin

COINS_COUNT, TARGET = map(int, stdin.readline().split())
COINS = sorted(map(int, stdin.read().split()), reverse=True)

CACHE = [[-1]*(COINS_COUNT+1) for _ in range(TARGET+1)]

def solve(target: int, begin_index: int) -> int:
    # target: [0, TARGET]
    # begin_index: [0, COINS_COUNT]

    cache_entry = CACHE[target][begin_index]
    if cache_entry != -1:
        return cache_entry

    # Handle base cases
    length = COINS_COUNT - begin_index
    if target == 0:
        return 1
    if length == 0:
        return 0
    if length == 1:
        return 1 if target % COINS[COINS_COUNT - 1] == 0 else 0

    current_coin = COINS[begin_index]
    result = sum(
        solve(target - i * current_coin, begin_index + 1)
        for i in range(target//current_coin + 1)
    )

    CACHE[target][begin_index] = result
    return result

answer = solve(TARGET, 0)
print(answer)
