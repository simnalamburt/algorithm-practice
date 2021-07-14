N = int(input())
print('\n'.join(' '*(N-n) + '*'*n for n in range (1, N+1)))
