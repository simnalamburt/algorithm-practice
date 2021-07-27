input()
print(sum(
    (ord(ch) - 96)*31**i
    for i, ch in enumerate(input())
) % 1234567891)
