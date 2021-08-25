N, K = map(int, input().split())
coins = [int(input()) for _ in range(N)]

## NOTE: DP가 아니라 그리디로 풀기
#DP = [0] + [None]*K
#for i in range(1, K+1):
#    DP[i] = 1 + min(
#        DP[i - coin]
#        for coin in coins
#        if i - coin >= 0
#    )
#answer = DP[-1]

count = 0
while K > 0:
    if not coins:
        # Impossible
        break
    coin = coins[-1]
    if K >= coin:
        count += K // coin
        K = K % coin
    else:
        coins.pop()
print(count)
