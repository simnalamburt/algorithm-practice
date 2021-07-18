for _ in range(int(input())):
    count = 0
    for ch in input():
        count += 1 if ch == '(' else -1
        if count < 0:
            break
    print('YES' if count == 0 else 'NO')
