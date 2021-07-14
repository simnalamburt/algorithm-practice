N = int(input())
words = {input() for _ in range(N)}
print('\n'.join(
    sorted(words, key=lambda word: (len(word), word))
))
