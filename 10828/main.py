stack = []

N = int(input())
for _ in range(N):
    cmd, *args = input().split()

    if cmd == 'push':
        stack.append(args[0])
    elif cmd == 'pop':
        if len(stack) == 0:
            print(-1)
        else:
            print(stack.pop())
    elif cmd == 'size':
        print(len(stack))
    elif cmd == 'empty':
        print(0 if stack else 1)
    elif cmd == 'top':
        if len(stack) == 0:
            print(-1)
        else:
            print(stack[-1])
