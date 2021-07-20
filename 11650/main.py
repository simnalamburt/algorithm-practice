N = int(input())
print('\n'.join(
    f'{x} {y}' for x, y in sorted(
        tuple(map(int, input().split())) for _ in range(N)
    )
))
