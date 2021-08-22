T = int(input())
for _ in range(T):
    n = int(input())
    DB = {}
    for i in range(n):
        _, typ = input().split()
        if typ in DB:
            DB[typ] += 1
        else:
            DB[typ] = 1
    mult = 1
    for v in DB.values():
        mult *= v + 1
    print(mult - 1)
