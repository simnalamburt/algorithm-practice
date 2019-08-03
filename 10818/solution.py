from re import finditer
from sys import stdin

def solution(string: str) -> tuple:
    minimum = +1000001
    maximum = -1000001
    for match in finditer(r'-?[0-9]+', string):
        number = int(match.group(0))
        if minimum > number:
            minimum = number
        if maximum < number:
            maximum = number
    return minimum, maximum

count = int(input())
string = stdin.read()
print(*solution(string))
