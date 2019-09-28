from functools import lru_cache

@lru_cache(None)
def solve(chapters: tuple) -> int:
    length = len(chapters)
    if length <= 1:
        return 0
    if length == 2:
        return sum(chapters)

    minimum = float('inf')
    for i in range(0, length-1):
        cost = chapters[i] + chapters[i+1]
        answer = solve(chapters[0:i] + (cost,) + chapters[i+2:]) + cost
        if minimum > answer:
            minimum = answer

    return minimum

for _ in range(int(input())):
    input()
    chapters = tuple(int(x) for x in input().split())
    # assert 3 <= len(chapters) <= 500
    # assert sum(chapters) <= 10000

    answer = solve(chapters)
    print(answer)
