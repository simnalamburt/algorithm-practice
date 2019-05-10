#!/usr/bin/env python3
def dist_square(p1: tuple, p2: tuple) -> int:
    return (p1[0] - p2[0])**2 + (p1[1] - p2[1])**2

def solve(src: tuple, dst: tuple, planets: list) -> int:
    return sum(
        1 for planet in planets if
        (dist_square(src, planet[:2]) <= planet[2]**2) != (dist_square(dst, planet[:2]) <= planet[2]**2)
    )

count = int(input())
for _ in range(count):
    x1, y1, x2, y2 = map(int, input().split())
    planets_count = int(input())

    start = (x1, y1)
    end = (x2, y2)
    planets = [
        tuple(int(x) for x in input().split())
        for _ in range(planets_count)
    ]

    result = solve(start, end, planets)
    print(result)
