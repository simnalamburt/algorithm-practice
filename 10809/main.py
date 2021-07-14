word = input()
print(' '.join(
    str(word.find(chr(ord('a') + i))) for i in range(26)
))
