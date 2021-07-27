table = [[0] * 15 for _ in range(15)]

for j in range(15):
    table[0][j] = j
for i in range(1, 15):
    for j in range(15):
        table[i][j] = sum(table[i-1][k] for k in range(j+1))

N = int(input())
for _ in range(N):
    k = int(input())
    n = int(input())
    print(table[k][n])
