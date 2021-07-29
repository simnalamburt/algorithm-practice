def solve(line: str) -> bool:
    stack = []
    for ch in line:
        if ch == '(' or ch == '[':
            stack.append(ch)
        elif ch == ')':
            if stack and stack[-1] == '(':
                stack.pop()
            else:
                return False
        elif ch == ']':
            if stack and stack[-1] == '[':
                stack.pop()
            else:
                return False
    return not stack

while (line := input()) != '.':
    print('yes' if solve(line) else 'no')
