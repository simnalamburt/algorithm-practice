from re import finditer

N = int(input())
input()
S = input()

query = 'I' + 'OI'*N
results = sum(1 for _ in finditer(f'(?={query})', S))
print(results)
