from sys import stdin

def solve(target: int, coins: list) -> int:
    length = len(coins)
    current_coin, *others = coins

    # Handle base cases
    if target == 0:
        return 1
    if length == 0:
        return 0
    if length == 1:
        return 1 if target % current_coin == 0 else 0

    return sum(
        solve(target - i * current_coin, others)
        for i in range(target//current_coin + 1)
    )

COINS_COUNT, TARGET = map(int, stdin.readline().split())
COINS = sorted(map(int, stdin.read().split()), reverse=True)
answer = solve(TARGET, COINS)
print(answer)
