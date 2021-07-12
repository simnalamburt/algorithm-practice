def calc(x1: int, y1: int, r1: int, x2: int, y2: int, r2: int) -> int:
    dist_square = (x1-x2)**2 + (y1-y2)**2
    inner_bound = (r1 - r2)**2
    outer_bound = (r1 + r2)**2

    if dist_square == 0 and r1 == r2:
        return -1
    if inner_bound < dist_square < outer_bound:
        return 2
    if dist_square in (inner_bound, outer_bound):
        return 1
    return 0

for _ in range(int(input())):
    print(calc(*map(int, input().split())))
