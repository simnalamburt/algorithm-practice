N = int(input())
print('\n'.join(sorted(
    (input() for _ in range(N)),
    key=lambda line: int(line.split()[0])
)))
