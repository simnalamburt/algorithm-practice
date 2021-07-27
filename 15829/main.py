input()
print(sum(
    (ord(ch) - ord('a') + 1)*31**i
    for i, ch in enumerate(input())
) % 1234567891)
