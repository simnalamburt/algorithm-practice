from typing import Union, Optional
from collections.abc import Iterable, Iterator

Token = Union[str, int]

def lex(line: Iterable[str]) -> Iterator[Token]:
    state: Optional[int] = None
    for ch in line:
        if '0' <= ch <= '9':
            if state is None:
                state = 0
            state = 10*state + ord(ch) - ord('0')
        else:
            if state is not None:
                yield state
                state = None
            yield ch
    if state is not None:
        yield state

def solve(tokens: Iterable[Token]) -> int:
    had_minus = False
    accum = 0
    for token in tokens:
        if isinstance(token, int):
            accum += -token if had_minus else token
        elif token == '-':
            had_minus = True
    return accum


line = input()
print(solve(lex(line)))
