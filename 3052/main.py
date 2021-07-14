bitset = 0
for _ in range(10):
    bitset |= 1 << int(input()) % 42
print(bin(bitset).count('1'))
