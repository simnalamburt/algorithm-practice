from sys import stdin

def solve(target: int, lines: list) -> int:
    # cases[x] : 동전들을 사용해 'x원'을 만들 수 있는 경우의 수
    cases = [1] + [0]*target

    # DP
    for line in lines:
        coin = int(line)
        for current in range(coin, target+1):
            cases[current] += cases[current - coin]

    return cases[target]

def main():
    target = int(stdin.readline().split()[1])
    lines = stdin.read().split()
    print(solve(target, lines))

if __name__ == '__main__':
    main()
