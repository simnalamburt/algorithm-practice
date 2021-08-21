def solve(n: int) -> int:
    upper_bound = int(n**0.5) + 1
    # O((n**0.5+3) C 3) = O(n**1.5)
    for b in range(upper_bound):
        for c in range(b, upper_bound):
            for d in range(c, upper_bound):
                if b**2 + c**2 + d**2 != n:
                    continue
                elif c == 0:
                    return 1
                elif b == 0:
                    return 2
                else:
                    return 3
    return 4

n = int(input())
print(solve(n))
