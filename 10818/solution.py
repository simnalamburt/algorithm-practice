from re import finditer
from sys import stdin
from math import inf

count = int(input())
minimum = inf
maximum = -inf
for match in finditer(r'-?[0-9]+', stdin.read()):
    number = int(match.group(0))
    minimum = min(minimum, number)
    maximum = max(maximum, number)
print(minimum, maximum)
