from sys import stdin

COINS_COUNT, TARGET = map(int, stdin.readline().split())
COINS = sorted(map(int, stdin.read().split()), reverse=True)

# begin_index == COINS_COUNT - 1
CACHE = [
    1 if target % COINS[COINS_COUNT - 1] == 0 else 0
    for target in range(TARGET+1)
]

for begin_index in range(COINS_COUNT - 2, -1, -1): # [0, COINS_COUNT - 2]
    current_coin = COINS[begin_index]

    for target in range(TARGET, 0, -1): # [1, TARGET]
        CACHE[target] = sum(
            CACHE[target - i*current_coin]
            for i in range(target//current_coin + 1)
        )

answer = CACHE[TARGET]
print(answer)
