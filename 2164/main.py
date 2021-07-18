def f(n):
    if n == 1:
        return 1
    if n%2 == 0:
        return 2*f(n//2)
    else:
        return 2*f(n//2+1) - 2

print(f(int(input())))
