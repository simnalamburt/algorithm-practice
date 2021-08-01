K, N = map(int, input().split())
cables = [int(input()) for _ in range(K)]

def calc(length: int) -> int:
    return sum(cable // length for cable in cables)

trial = 0

# Naive 버전: calc 함수는 입력이 작을수록 큰 숫자가 나오니까,
# 큰 입력에서 시작해서 점점 줄여나가면 된다.
for length in range(sum(cables) // N, 0, -1):
    n = calc(length)

    trial += 1
    print(f'{length=} {n=}')

    if n >= N:
        break

print(f'{length=} {trial=}')
