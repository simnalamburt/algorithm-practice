N = int(input())
for _ in range(N):
    count, word = input().split()
    count = int(count)
    print(''.join(c * count for c in word))
