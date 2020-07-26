#!/usr/bin/env python3
from itertools import combinations

def one_bits_in_bitset(bitset: int) -> int:
    '''
    정수 bitset를 이진수로 표기했을 때, 1bit가 몇개나 나타나는지 알아내는 함수

    Examples:
      one_bits_in_bitset(0b00000000) = 0
      one_bits_in_bitset(0b10010000) = 2
      one_bits_in_bitset(0b11111111) = 8
    '''
    w = 0
    while bitset:
        w += 1
        bitset &= bitset - 1
    return w

# guitar_count: 기타의 수
guitar_count, _ = map(int, input().split())

# DATA[x]: x번째 기타가 칠 수 있는 노래를 비트셋으로 표현한것
#
# 입력이 아래와 같을 경우:
#     4 5
#     A YYYNN
#     B YYNNY
#     C NNNYY
#     D YNNNN
#
# DATA는 아래와 같음:
#     DATA = [
#       0b00111,
#       0b10011,
#       0b11000,
#       0b00001,
#     ] = [7, 19, 24, 1]
DATA = []
for i in range(guitar_count):
    _, param = input().split()
    DATA.append(sum(
        1 << n for n, x in enumerate(param) if x == 'Y'
    ))

number_of_songs = 0
number_of_guitars = -1
for count in range(1, guitar_count + 1):
    for combination in combinations(DATA, count):
        union = 0
        for n in combination:
            union |= n

        songs = one_bits_in_bitset(union)
        if songs > number_of_songs:
            number_of_songs = songs
            number_of_guitars = len(combination)

print(number_of_guitars)
