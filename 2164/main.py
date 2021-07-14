N = int(input())

cards = [*range(1, N+1)] + [0]*N

start = 0
end = N

while end - start > 1:
    cards[end] = cards[start + 1]
    start += 2
    end += 1

print(cards[start])
