T = int(input())
for _ in range(T):
    N, M = map(int, input().split())
    docs = list(map(int, input().split()))

    target = docs[M]
    count = 0
    last_idx = 0
    for p in reversed(range(target, 10)):
        for i in range(last_idx, last_idx + N):
            i %= N
            if docs[i] != p:
                continue
            count += 1
            last_idx = i
            if i == M:
                break

    print(count)
