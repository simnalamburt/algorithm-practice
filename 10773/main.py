N = int(input())

stack = []
for _ in range(N):
    n = int(input())
    if n != 0:
        stack.append(n)
    elif stack:
        stack.pop()
print(sum(stack))
