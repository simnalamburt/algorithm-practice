#!/usr/bin/env python3
def popcount(bitset: int) -> int:
    '''
    정수 bitset를 이진수로 표기했을 때, 1bit가 몇개나 나타나는지 알아내는 함수

    Examples:
      popcount(0b00000000) = 0
      popcount(0b10010000) = 2
      popcount(0b11111111) = 8
    '''
    w = 0
    while bitset:
        w += 1
        bitset &= bitset - 1
    return w

def bitset_union(generator) -> int:
    union = 0
    for n in generator:
        union |= n
    return union

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
N, _ = map(int, input().split())

for i in range(N):
    _, param = input().split()
    bitset = sum(1 << n for n, x in enumerate(param) if x == 'Y')
    DATA.append(bitset)

songs_max = 0
guitars_min = -1
for bitset_guitars in range(0, 1 << N):
    bitset_songs = bitset_union(DATA[i] for i in range(N) if bitset_guitars & (1 << i))
    count_guitars = popcount(bitset_guitars)
    count_songs = popcount(bitset_songs)

    if count_songs > songs_max:
        songs_max = count_songs;
        guitars_min = count_guitars;
    elif count_songs == songs_max and count_guitars < guitars_min:
        guitars_min = count_guitars;

print(guitars_min)
