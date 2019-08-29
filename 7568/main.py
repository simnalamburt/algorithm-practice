#!/usr/bin/env python3
# https://www.acmicpc.net/problem/7568
from dataclasses import dataclass
from sys import stdin

# 데이터클래스
# Reference: https://docs.python.org/3/library/dataclasses.html
@dataclass
class Person:
    weight: int
    height: int

    # '<' 연산자 정의
    # Reference: https://docs.python.org/3/reference/datamodel.html#object.__lt__
    def __lt__(self, other) -> bool:
        return self.weight < other.weight and self.height < other.height

stdin.readline()
people = [Person(*map(int, line.split())) for line in stdin.readlines()]
print(' '.join(
    str(sum(1 for e in people if person < e) + 1)
    for person in people
))
