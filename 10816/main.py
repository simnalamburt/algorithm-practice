from collections import defaultdict

counts = defaultdict(int)

input()
for card in input().split():
    counts[int(card)] += 1

input()
print(' '.join(
    str(counts[int(query)]) for query in input().split()
))
