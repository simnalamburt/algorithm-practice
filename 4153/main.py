while True:
    a, b, c = sorted(map(int, input().split()))
    if a == b == c == 0:
        break
    print('right' if a*a + b*b == c*c else 'wrong')
