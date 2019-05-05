num = int(input())
a = 0
b = 1
while num > 0:
    tmp = a + b
    a, b = b, tmp
    num -= 1
print(a)
