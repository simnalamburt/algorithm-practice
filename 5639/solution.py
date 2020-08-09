from sys import setrecursionlimit, stdin
from math import inf

INPUTS = [*map(int, stdin), inf]

def solve(idx: int = 0, upper_bound = 1_000_000) -> int:
    pivot = INPUTS[idx]
    # pivot이 upper_bound 보다 크다 = 이 트리는 Nil이다
    if upper_bound < pivot:
        return idx

    # 왼쪽 서브트리가 끝나는 인덱스 == 오른쪽 서브트리 시작지점 인덱스
    idx_right = solve(idx + 1, pivot)
    # 오른쪽 서브트리가 끝나는 인덱스
    idx_end = solve(idx_right, upper_bound)

    # 방문
    print(pivot)

    # 트리가 끝난 지점 리턴
    return idx_end

setrecursionlimit(10050)
solve()
