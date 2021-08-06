# f(n) = f(n-1) + f(n-2) + f(n-3)
answer = [None, 1, 2, 4, 7, 13, 24, 44, 81, 149, 274]
T = int(input())
for _ in range(T):
    print(answer[int(input())])
