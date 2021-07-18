def f(line: str) -> bool:
    count = 0
    for ch in line:
        count += 1 if ch == '(' else -1
        if count < 0:
            return False
    return True if count == 0 else False

N = int(input())
for _ in range(N):
    print('YES' if f(input()) else 'NO')
