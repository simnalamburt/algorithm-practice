N = int(input())
for i in range(N):
    if N == i + sum(map(int, str(i))):
        print(i)
        exit(0)
print(0)
