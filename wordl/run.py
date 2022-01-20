# xz -dc targets.xz | python3 run.py
from sys import stdin
from itertools import combinations

def word_to_bitset(word: str) -> int:
    result = 0
    for char in word:
        code = ord(char)
        if ord('a') <= code <= ord('z'):
            result |= 1 << (ord(char) - ord('a'))
    return result

goal = word_to_bitset('abcdefghijklmnopqrstuvwxyz')
print(f'{goal=}')

words = [(word, word_to_bitset(word)) for word in stdin.read().split("\n") if len(word) == 11]

num_words = len(words)
num_combinations = num_words*(num_words - 1)*(num_words - 2)//6

print(f'number of words with 11 letters: {num_words}')
print(f'number of possible combinations: {num_combinations}')

for i, ((w0, s0), (w1, s1), (w2, s2)) in enumerate(combinations(words, 3)):
    if i % 10_000_000 == 0:
        print(f'{i:10} ({i*100/num_combinations:.03}%)')
    if s0 | s1 | s2 == goal:
        print(w0, w1, w2)
