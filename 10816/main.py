from collections import defaultdict

N = int(input())
cards = [*map(int, input().split())]
M = int(input())
queries = [*map(int, input().split())]

counts = defaultdict(int)
for card in cards:
    counts[card] += 1

print(' '.join(str(counts[query]) for query in queries))
