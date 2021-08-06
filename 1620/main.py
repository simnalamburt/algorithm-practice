N, M = map(int, input().split())
names = [input() for _ in range(N)]
name_to_num = {name: i + 1 for i, name in enumerate(names)}

for _ in range(M):
    query = input()
    if 'A' <= query[0] <= 'Z':
        # 영어
        print(name_to_num[query])
    else:
        # 숫자
        number = int(query)
        print(names[number - 1])
