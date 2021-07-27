N = int(input())

arr = [None]*N
for i in range(N):
    x, y = map(int, input().split())
    arr[i] = (y, x)
arr.sort()
for y, x in arr:
    print(f'{x} {y}')
