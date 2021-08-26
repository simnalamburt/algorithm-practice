from typing import Optional
from collections.abc import Iterable, Iterator

Token = tuple[str, int]

def lex(line: Iterable[str]) -> Iterator[Token]:
    op: str = '+'
    num: int = 0
    for ch in line:
        if '0' <= ch <= '9':
            num = 10*num + ord(ch) - ord('0')
        else:
            yield op, num
            op = ch
            num = 0
    yield op, num

def minimize(tokens: list[Token]) -> tuple[int, str]:
    if len(tokens) == 0:
        return 0, ''

    (op, l), *rest = tokens
    if op == '+':
        r, rexp = minimize(rest)
        return +l+r, f'+{l}{rexp}'

    rmin, rminexp = minimize(rest)
    rmax, rmaxexp = maximize(rest)
    assert rmin <= rmax
    return min(
        (-l+rmin, f'-{l}{rminexp}'),
        (-(l+rmax), f'-({l}{rmaxexp})'),
    )

def maximize(tokens: list[Token]) -> tuple[int, str]:
    if len(tokens) == 0:
        return 0, ''

    (op, l), *rest = tokens
    if op == '+':
        r, rexp = maximize(rest)
        return +l+r, f'+{l}{rexp}'

    rmin, rminexp = minimize(rest)
    rmax, rmaxexp = maximize(rest)
    assert rmin <= rmax
    return max(
        (-(l+rmin), f'-({l}{rminexp})'),
        (-l+rmax, f'-{l}{rmaxexp}')
    )

line = input()
lexed = list(lex(line))
print(lexed)
print(minimize(lexed))
print(maximize(lexed))
