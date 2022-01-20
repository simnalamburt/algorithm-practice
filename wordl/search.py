# xz -dc targets.xz | python3 cheat.py
from sys import stdin
from re import fullmatch

REGEX = r'[laedfgjkxz]e[laedfgjkxz]{3}'

for word in stdin.read().split("\n"):
    if len(word) != 5:
        continue
    if word == '*****':
        continue
    if fullmatch(REGEX, word) is None:
        continue

    print(f'{word}')
