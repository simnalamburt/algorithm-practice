M, N = map(int, input().split())

sieve = [False, False] + [True]*(N-1)
for i in range(2, N+1):
    if not sieve[i]:
        continue
    for j in range(i*2, N+1, i):
        sieve[j] = False

print('\n'.join(str(i) for i in range(M, N+1) if sieve[i]))
