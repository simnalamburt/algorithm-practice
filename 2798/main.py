import itertools

N, M = map(int, input().split())

print(max(
    added
    for triple in itertools.combinations(map(int, input().split()), 3)
    if (added := sum(triple)) <= M
))
