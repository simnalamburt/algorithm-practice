_, X = map(int, input().split())
print(' '.join(n for n in input().split() if int(n) < X))
