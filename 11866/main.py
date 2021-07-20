def f(N, K):
    circle = [*range(1, N+1)]
    pos = -1
    while circle:
        pos += K
        pos %= len(circle)
        yield circle.pop(pos)
        pos -= 1

N, K = map(int, input().split())
print('<' + ', '.join(map(str, f(N, K))) + '>')
