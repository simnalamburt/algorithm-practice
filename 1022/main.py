from math import log10, floor

def value_of(x: int, y: int) -> int:
    '''
    좌표 (x, y) 를 입력하면 해당 좌표에 맞는 값을 출력하는 함수
    '''

    if -y < x <= y:
        return (2*y + 1)**2 + x - y
    if x < y <= -x:
        return (-2*x + 1)**2 + 3*x + y
    if y < -x <= -y:
        return (-2*y + 1)**2 + 5*y-x
    if -x < -y <= x:
        return (2*x + 1)**2 - 7*x - y
    return 1

# 입력 받음
r1, c1, r2, c2 = map(int, input().split())

# 테이블 초기화
width = c2 - c1 + 1
height = r2 - c1 + 1
table = [[0]*width for _ in range(height)]
for y in range(r1, r2 + 1):
    for x in range(c1, c2 + 1):
        table[y - r1][x - c1] = value_of(x, y)

# 칼럼 가로길이 측정
width_list = [
    # floor(log10(x)) + 1 하면 자리수가 나온다
    #
    # Examples:
    #   log10(11) = 1.0xx       floor(log10(11)) = 2
    #   log10(10) = 1           floor(log10(10)) = 2
    #   log10(9)  = 0.9xx       floor(log10(9))  = 1
    floor(max(log10(table[y][x]) for y in range(height))) + 1
    for x in range(width)
]

# 문자열 조립
answer = '\n'.join(
    ' '.join(
        str(table[y][x]).rjust(width_list[x])
        for x in range(width)
    )
    for y in range(height)
)

print(answer)
