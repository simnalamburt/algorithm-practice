table = [True]*1001
table[0] = False
table[1] = False
for i in range(2, 1001):
    if table[i]:
        for j in range(i*2, 1001, i):
            table[j] = False

input()
print(sum(1 for w in input().split() if table[int(w)]))
