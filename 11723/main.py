M = int(input())

S = set()
for _ in range(M):
    cmd, *rest = input().split()
    if cmd == 'add':
        x = int(rest[0])
        S.add(x)
    elif cmd == 'remove':
        x = int(rest[0])
        if x in S:
            S.remove(x)
    elif cmd == 'check':
        x = int(rest[0])
        print(1 if x in S else 0)
    elif cmd == 'toggle':
        x = int(rest[0])
        if x in S:
            S.remove(x)
        else:
            S.add(x)
    elif cmd == 'all':
        S = {1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}
    elif cmd == 'empty':
        S = set()

# NOTE: set 메서드명 기억에 확신 없었음, S.remove 하기 전에 존재성 체크 잊었었음
