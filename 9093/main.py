from sys import stdin

def main():
    next(stdin)
    input = stdin.read()

    for line in input.splitlines():
        line = line.strip()
        print(' '.join(word[::-1] for word in line.split(' ')))

if __name__ == '__main__':
    main()
