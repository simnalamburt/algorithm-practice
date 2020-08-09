from sys import setrecursionlimit, stdin
from math import inf

INPUTS = [*map(int, stdin), inf]

def solve(idx: int = 0, upper_bound = inf) -> int:
    pivot = INPUTS[idx]
    if upper_bound < pivot:
        return idx

    # 왼쪽 서브트리가 끝나는 인덱스 == 오른쪽 서브트리 시작지점 인덱스
    idx_right = solve(idx + 1, pivot)

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
