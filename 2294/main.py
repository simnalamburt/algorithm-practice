from sys import stdin
from math import inf

def solve(target: int, coins) -> int:
    # counts[x]: 현재까지 입력받은 동전들을 사용해, 'x원'을 만들고자 할 때
    # 필요한 최소 동전 수
    counts = [0] + [inf]*target

    # DP
    for coin in coins:
        for current in range(coin, target+1):
            counts[current] = min(counts[current], 1 + counts[current - coin])

    return counts[target]

def main():
    target = int(stdin.readline().split()[1])
    lines = stdin.read().split()
    answer = solve(target, map(int, lines))
    if answer == inf:
        print('-1')
    else:
        print(answer)

if __name__ == '__main__':
    main()
