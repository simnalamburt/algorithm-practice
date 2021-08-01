n = int(input())

stack = []
cmds = []
upcoming = 1
for _ in range(n):
    X = int(input())
    while X >= upcoming:
        stack.append(upcoming)
        upcoming += 1
        cmds.append('+')
    if stack and stack[-1] == X:
        stack.pop()
        cmds.append('-')
    else:
        print('NO')
        exit()

print('\n'.join(cmds))
