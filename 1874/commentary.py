n = int(input())

stack = []
result = []
upcoming = 1

def push():
    global upcoming
    stack.append(upcoming)
    upcoming += 1
    print(f'+ [..., {upcoming}]', stack, result)

def pop():
    result.append(stack.pop())
    print(f'- [..., {upcoming}]', stack, result)

print(f'  [..., {upcoming}]', stack, result)

for _ in range(n):
    X = int(input())

    # 이 시점에서 'X'를 뽑는 방법은
    # stack의 top에서 찾기, upcoming에서 찾기 둘 중 하나 뿐이다.

    # 숫자가 upcoming에 들어있는 경우, upcoming을
    # 여럿 뽑아서 원하는 숫자를 스택에 넣는다.
    while X >= upcoming:
        push()

    # 이제 'X'를 뽑는 방법은 stack의 top에서 찾기가 유일하다.

    if stack and stack[-1] == X:
        pop()
    else:
        # Impossible
        print('NO')
        break
