from sys import stdin
next(stdin)
for line in stdin:
    line = line.strip()
    print(' '.join(word[::-1] for word in line.split(' ')))
