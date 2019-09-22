from math import log10, floor

def init_table(x0: int, y0: int, width: int, height: int) -> list:
    '''
    테이블 초기화
    '''
    return [
        [
            (2*y + 1)**2 + x - y if -y < x <= y else
            (-2*x + 1)**2 + 3*x + y if x < y <= -x else
            (-2*y + 1)**2 + 5*y-x if y < -x <= -y else
            (2*x + 1)**2 - 7*x - y if -x < -y <= x else
            1
            for x in range(x0, x0 + width)
        ]
        for y in range(y0, y0 + height)
    ]

def find_length(table: list) -> int:
    '''
    입력된 테이블 안에 있는 숫자중 가장 큰 숫자의 자리수를 출력한다
    '''

    biggest = max(
        log10(elem)
        for row in table
        for elem in row
    )

    # floor(log10(x)) + 1 하면 자리수가 나온다
    #
    # Examples:
    #   log10(11) = 1.0xx       floor(log10(11)) = 2
    #   log10(10) = 1           floor(log10(10)) = 2
    #   log10(9)  = 0.9xx       floor(log10(9))  = 1
    return floor(biggest) + 1

def format_table(table: list, length: int) -> str:
    return '\n'.join(
        ' '.join(str(elem).rjust(length) for elem in row)
        for row in table
    )

y0, x0, y1, x1 = map(int, input().split())
width, height = x1 - x0 + 1, y1 - y0 + 1
table = init_table(x0, y0, width, height)
length = find_length(table)
print(format_table(table, length))
