while True:
    line = input()
    if line == '0':
        break
    print('yes' if line == line[::-1] else 'no')
