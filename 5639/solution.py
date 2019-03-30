from sys import setrecursionlimit, stdin
from math import inf

INPUTS = [*map(int, stdin), inf]

def solve(idx: int = 0, upper_bound = inf) -> int:
    pivot = INPUTS[idx]

    # 오른쪽 자식의 인덱스
    idx_right = (
        # 왼쪽 자식이 존재할 경우
        solve(idx + 1, min(upper_bound, pivot))
        if pivot > INPUTS[idx + 1] else
        # 왼쪽 자식이 존재하지 않을 경우
        idx + 1
    )

    # 트리가 끝난 지점의 인덱스
    idx_end = (
        # 오른쪽 자식이 존재할 경우
        solve(idx_right, upper_bound)
        if upper_bound > INPUTS[idx_right] else
        # 오른쪽 자식이 존재하지 않을 경우
        idx_right
    )

    # 프린트
    print(pivot)

    return idx_end

setrecursionlimit(10050)
solve()
