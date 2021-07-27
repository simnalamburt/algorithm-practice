N = int(input())

N -= 1
i = 1

while N > 0:
    N -= i*6
    i += 1

print(i)
