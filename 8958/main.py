N = int(input())
for _ in range(N):
    score = 0
    combo = 1
    for ox in input():
        if ox == 'O':
            score += combo
            combo += 1
        else:
            combo = 1
    print(score)
