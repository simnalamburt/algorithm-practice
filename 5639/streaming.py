from sys import setrecursionlimit, stdin
from math import inf

READ_AGAIN = False

def inputgen():
    for line in stdin:
        num = int(line)
        yield num

        global READ_AGAIN
        while READ_AGAIN:
            READ_AGAIN = False
            yield num

    while True:
        yield inf

INPUTS = inputgen()


def solve(upper_bound: int) -> None:
    pivot = next(INPUTS)

    # pivot이 upper_bound 보다 크다 = 이 트리는 Nil이다
    if upper_bound < pivot:
        global READ_AGAIN
        READ_AGAIN = True
        return

    # 왼쪽 서브트리가 끝나는 인덱스 == 오른쪽 서브트리 시작지점 인덱스
    solve(pivot)
    # 오른쪽 서브트리가 끝나는 인덱스
    solve(upper_bound)
    # 방문
    print(pivot)

setrecursionlimit(10050)
solve(1_000_000)
