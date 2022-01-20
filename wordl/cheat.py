# xz -dc targets.xz | python3 cheat.py
from sys import stdin

def word_to_bitset(word: str) -> int:
    result = 0
    for char in word:
        code = ord(char)
        if ord('a') <= code <= ord('z'):
            result |= 1 << (ord(char) - ord('a'))
    return result

words = stdin.read().split("\n")

cheats = ['their', 'would', 'fancy', 'speak', 'jumbo']
cheats = ['width', 'curse', 'among', 'bulky'] # fjpqvxz

for word in words:
    if len(word) != 5:
        continue
    if word == '*****':
        continue

    mask = 0
    for cheat in cheats:
        mask |= word_to_bitset(cheat)
    new_count = bin(word_to_bitset(word) & ~mask).count('1')
    if new_count < 1:
        continue

    print(f'{word} ({new_count})')
