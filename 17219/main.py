N, M = map(int, input().split())

db = {}
for _ in range(N):
    site, password = input().split()
    db[site] = password
for _ in range(M):
    site = input()
    print(db[site])
