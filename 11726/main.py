n = int(input())
a, b = 0, 1
for _ in range(n):
    a, b = b, a + b
print(b % 10007)
