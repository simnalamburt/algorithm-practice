N = int(input())
for _ in range(N):
    H, W, N = map(int, input().split())
    print(f'{(N-1)%H + 1}{(N-1)//H + 1:02}')
